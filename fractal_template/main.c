#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libfractal/fractal.h"
#define d "-d"
#define mt "--maxthreads"
#define MAXLEN 1000

int nbFiles =0;
int printAll = 0;
int maxThreads = 1;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
struct fract *buffer;

void *readerFunc(void *param) { //Producteur
  FILE *fichier = NULL;

  fichier = fopen((char *) param, "r");
  char current[MAXLEN];
  while (fgets(current, MAXLEN, fichier) != NULL){
    if (current[0] != '\n' && current[0] != '#'){
      //Production de l item
      char *n = strtok(str, delim);
      char *name = (char *) malloc(strlen(n) * sizeof(char));
      name = n;
      int w = atoi(strtok(NULL, delim));
      int h = atoi(strtok(NULL, delim));
      double a = atof(strtok(NULL, delim));
      double b = atoi(strtok(NULL, delim));
      struct fract *temp = fractal_new(name, w, h, a, b);
      sem_wait(&empty);
      pthread_mutex_lock(&mutex);
      //Section Critique
      int placed = 0;
      for (int i = 0; !placed; i++) {
        if (buffer[i] == NULL) {
          buffer[i] = temp;
          placed ++;
        }
      }
      //La structure a été placée pour le calcul
      pthread_mutex_unlock(&mutex);
      sem_post(&full);
    }
  }


  fclose(fichier);
  return NULL;
}

int main(int argc, char const *argv[]) {
  const char *files[argc];
  const char *fileOut = argv[argc-1];

  //On checke les arguments d entree
  for (int i = 1; i < argc-1; i++) {

    //On regarde si l'argument i est -d
    if (strcmp(argv[i], d) == 0) printAll = 1; //On imprime tout
    else {
      if (strcmp(argv[i], mt) == 0) {
        maxThreads = atoi(argv[i+1]);
        i++;
      }
      else {
        files[nbFiles] = argv[i];
        nbFiles++;
      }
    }
  }

  printf("Nombre de fichier : %i\n", nbFiles);
  printf("Doit on tout imprimer ? : %i\n", printAll);
  printf("Fichier de sortie : %s\n", fileOut);
  for (int i = 0; i < nbFiles; i++) printf("Fichier de donnee n° %i : %s\n", i+1, files[i]);

  //Initialisation des semaphores et du mutex
  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, N);
  sem_init(&full, 0,0);
  buffer = (struct fract *) malloc(maxThreads * sizeof(struct fract));







  return 0;
}
