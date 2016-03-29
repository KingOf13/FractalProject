#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libfractal/fractal.h"
#define d "-d"
#define mt "--maxthreads"

int nbFiles =0;
int printAll = 0;
int maxThreads = 1;

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
  for (int i = 0; i < nbFiles; i++) printf("Fichier de donnée n° %i : %s\n", i+1, files[i]);







  return 0;
}
