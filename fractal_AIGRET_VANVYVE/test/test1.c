/*
Systemes Informatique LSINF1252
Projet 2 :  Fractales

AIGRET Julien   8343-13-00
VANVYVE Nicolas 6590-13-00

MAI 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "../libfractal/fractal.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/*
  Tests en CUnit pour le projet 2.
*/

/*
Idees de test

Creer une nouvelle fractale
vérifier la taille allouée??
donner une grille deja faite et tester les valeur
idem inversément
verifier que le longueur est ok
idem largeur
idem a
idem b

Tester le format --> a mettre dans 


*/


/*
// Test si alloc passe bien à 0 apres myfree
void test_myfree_desalloc(void)
{
  int* pointeurtest = (int *) mymalloc(sizeof(int));
  block_header *bh_test = (block_header *)(pointeurtest-1);
  myfree(pointeurtest);
  CU_ASSERT_EQUAL((bh_test->alloc),0);
}
*/


void test_getter(char *name, int w, int h, double a, double b)
{
  struct fractal *fract_test = fractal_new(name,w,h,a,b);
  CU_ASSERT_EQUAL(fractal_get_width(fract_test),w);
  CU_ASSERT_EQUAL(fractal_get_height(fract_test),h);
  CU_ASSERT_EQUAL(fractal_get_a(fract_test),a);
  CU_ASSERT_EQUAL(fractal_get_b(fract_test),b);
}


int setup(void)  { return 0; }
int teardown(void) { return 0; }

int main()
{
  char *name = (char *) malloc(strlen("fract_test") * sizeof(char));
  name = "fract_test";
  int w = 30;
  int h = 30;
  double a = 0.4;
  double b = 0.6;
  struct fractal *fract_test = fractal_new(name,w,h,a,b);

  CU_pSuite pSuite = NULL;
  if (CUE_SUCCESS != CU_initialize_registry())
  return CU_get_error();

  pSuite = CU_add_suite("Projet-Fractales", setup, teardown);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

   if ((NULL == CU_add_test(pSuite, "Test getter",test_getter)) ||
       (NULL == CU_add_test(pSuite, "/* ... */ ", /* ... */ ))
     )
   {
     CU_cleanup_registry();
     return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   CU_cleanup_registry();
   return CU_get_error();
}
