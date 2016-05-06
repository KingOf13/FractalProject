#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "libfractal/fractal.h"
#define d "-d"
#define mt "--maxthreads"
#define MAXLEN 1000

/*
Notes :
- Si le fichier ne contient que une ligne de commentaire --> La fonction attend et ne fait rien
- Idem si le fichier est vide (Astuce Tuer le processus - Moniteur systeme --> main)
*/

int nbFiles =0;
int printAll = 0;
int maxThreads = 1;
int stdinUsed = 0;
const char *STDIN = "stdin";
const char *delim = " ";
struct fractal *best = NULL; // On stock la meilleure fractale dans une variable globale
double bestAverage = 0;


void *readerFunc(void *param);
void *computeFunc (void *param);
pthread_mutex_t mutex_buffer;
pthread_mutex_t mutex_closing;
pthread_mutex_t mutex_best;
sem_t empty;
sem_t full;

pthread_t *readThreads;
pthread_t *computeThreads;

struct fractal **buffer;
int isReading;

int main(int argc, char const *argv[]) {
  const char *files[argc];
  const char *fileOut = argv[argc-1];

  //On checke les arguments d'entree
  for (int i = 1; i < argc-1; i++) {

    //On regarde si l'argument i est -d
    if (strcmp(argv[i], d) == 0) printAll = 1; //On imprime tout
    else {
      if (strcmp(argv[i], mt) == 0) { //Si l'utilisateur a indique un nombre max de thread,
      maxThreads = atoi(argv[i+1]); // on regle le nombre maximal de thread a ce nombre
      i++; // et on saute une case du tableau d'arguments
      }
      else { // Si ce n'est ni un -d ni un --maxthreads, c'est un nom de fichier
        if ((strcmp(argv[i], "-") == 0)) {
          if (stdinUsed) {
            fprintf(stderr, "L'entree standard a ete indiquee plusieurs fois comme source. Elle n'est prise en compte qu'une fois\n");
          }
          else {
            stdinUsed = 1;
            files[nbFiles] = STDIN;
            nbFiles++;
          }
        }
        else {
          files[nbFiles] = argv[i];
          nbFiles++;
      }
    }
  }
}

printf("Nombre de fichier : %i\n", nbFiles);
printf("Doit on tout imprimer ? : "); if(printAll) printf("Oui\n"); else printf("Non\n");
printf("Fichier de sortie : %s\n", fileOut);

for (int i = 0; i < nbFiles; i++) printf("Fichier de donnee n° %i : %s\n", i+1, files[i]);

//Initialisation des semaphores et des mutex
pthread_mutex_init(&mutex_buffer, NULL);
pthread_mutex_init(&mutex_closing, NULL);
pthread_mutex_init(&mutex_best, NULL);
sem_init(&empty, 0, maxThreads);
sem_init(&full, 0,0);

buffer = (struct fractal **) malloc(maxThreads * sizeof(struct fractal *));
if (buffer==NULL) exit(EXIT_FAILURE);
isReading = nbFiles;

readThreads = (pthread_t *) malloc(nbFiles * sizeof(pthread_t));
computeThreads = (pthread_t *) malloc(maxThreads * sizeof(pthread_t));
int arg[maxThreads];
int err;

if (stdinUsed) {
  printf("Pour entrer du texte sur stdin, respecter le schema \"name w h a b\"\n");
  printf("Pour terminer, appuyez sur ctrl + D sous Linux et ctrl + Z sous Windows\n");
}
for (int i = 0; i < nbFiles; i++) {

  err = pthread_create(&(readThreads[i]), NULL, readerFunc,(void *)files[i]);
  if (err != 0) fprintf(stderr, "Erreur lors de la creation du reader n° %i\n", i);
}

for (int i = 0; i < maxThreads; i++) {
  arg[i] = i;
  err=pthread_create(&(computeThreads[i]), NULL, computeFunc, &(arg[i]));
  if (err != 0) fprintf(stderr, "Erreur lors de la creation du thread de calcul n° %i\n", i);
}

struct fractal *best = NULL;


printf("ENTREE DANS LE RETOUR\n");

for (int i = 0; i < maxThreads; i++) {
  struct fractal *temp;
  err=pthread_join(computeThreads[i], (void **) &temp);
  if (err != 0) fprintf(stderr, "Erreur lors du join du thread de calcul n° %i\n", i);
  if (best == NULL) best = temp;
  else  if (best->average < temp->average) {
  printf("Récupération de best du thread %i\n",i);
  fractal_free((struct fractal*) best);
  best = (struct fractal *) temp;
  }
  else fractal_free(temp);
  }

  printf("SORTIE DU RETOUR\n");

  err = write_bitmap_sdl(best, fileOut);

  if (err != 0) {
    fprintf(stderr, "Erreur lors de l'ecriture de la meilleure fractale\n");
  }
return err;
}


//PRODUCTEUR
void *readerFunc(void *param) {

  FILE *fichier = NULL;
  const char* nomfichier = (char *) param;

  if (strcmp(nomfichier, STDIN) == 0) {
    fichier = stdin;
  }
  else {
    fichier = fopen(nomfichier, "r");
  }
  if (fichier == NULL) fprintf(stderr, "Erreur lors de l'ouverture du fichier  : %s\n", (char *) param);
  char current[MAXLEN];
  while (fgets(current, MAXLEN, fichier) != NULL){
    if (current[0] != '\n' && current[0] != '#'){
      //Production de l item
      char *n = strtok(current, delim);
      char *name = (char *) malloc(strlen(n) * sizeof(char));
      name = n;

      int w = atoi(strtok(NULL, delim));
      int h = atoi(strtok(NULL, delim));
      double a = atof(strtok(NULL, delim));
      double b = atof(strtok(NULL, delim));
      struct fractal *temp = fractal_new(name, w, h, a, b);
      sem_wait(&empty);
      pthread_mutex_lock(&mutex_buffer);
      //Section Critique
      int placed = 0;
      for (int i = 0; !placed; i++) {
        if (buffer[i] == NULL) {
          buffer[i] = temp;
          placed ++;
        }
      }
			sem_post(&full);
      //La structure a été placée pour le calcul : fin de la Section Critique
      pthread_mutex_unlock(&mutex_buffer);
    }
  }

  //On essaie de fermer le fichier
  int err = fclose(fichier);
  if (err != 0)
  {
    fprintf(stderr, "Erreur lors de la fermeture du fichier : %s\n",   (char *) param);
  }
  //Pour marquer qu'on a bien ferme le fichier
  pthread_mutex_lock(&mutex_closing);
  isReading--;
  pthread_mutex_unlock(&mutex_closing);
  return NULL;

}


//CONSOMMATEUR
void *computeFunc (void *param) {
  struct fractal *best = NULL;
  struct fractal *temp;
  int bestAverage = 0;


  int *arg = (int *) param; //La case du buffer qui lui est attribuee

  while (isReading != 0 ) {
    temp = NULL;
		sem_wait(&full);
		pthread_mutex_lock(&mutex_buffer);
		//Section Critique
		int get = 0;
		for (int i = 0; !get; i++) {
			if (buffer[i] != NULL) {
				temp = buffer[i];
				get ++;
        buffer[i] = NULL;
			}
		}
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&empty);


    int w = fractal_get_width(temp);
    int h = fractal_get_height(temp);
    double average = 0;
    double total = w * h;
    for (int x = 0; x < w; x++) {
      for (int y = 0; y < h; y++) {
        int val = fractal_compute_value(temp, x, y);
        average += val;
      }
    }


    average = average / total;

    temp->average = average;


    char n[1000] = "";
    char *name = n;
    strcpy(name, temp->name);
    strcat(name, ".bmp");
    if (printAll) write_bitmap_sdl(temp, name);

    if ( average < bestAverage)
    {
      fractal_free(temp);
    }
    else
    {
      bestAverage = average;
      if (best != NULL) fractal_free(best);
      best = temp;
    }
  }
  return (void*) best;
}
