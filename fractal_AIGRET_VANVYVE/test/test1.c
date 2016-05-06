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
Idees de tests
[...]
*/

void test_getter(char *name, int w, int h, double a, double b)
{
  struct fractal *fract_test = fractal_new(name,w,h,a,b);
  CU_ASSERT_EQUAL(fractal_get_width(fract_test),w);
  CU_ASSERT_EQUAL(fractal_get_height(fract_test),h);
  CU_ASSERT_EQUAL(fractal_get_a(fract_test),a);
  CU_ASSERT_EQUAL(fractal_get_b(fract_test),b);
}

void test_get_value()
{
  char *name = (char *) malloc(strlen("fract_test") * sizeof(char));
  name = "fract_test";
  int size = 10;
  struct fractal *fract_test =  fractal_new(name,size,size,1,1);

  int *matrix;
  matrix = (int *) malloc( size*size * sizeof(int));

  for (int i = 0; i < size*size; i++)
  {
    *(matrix+i)=i;
  }
  int k = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      CU_ASSERT_EQUAL(fractal_get_value(fract_test,i,j),k);
      k++;
    }
  }
}

void test_set_value()
{
  char *name = (char *) malloc(strlen("fract_test") * sizeof(char));
  name = "fract_test";
  int size = 10;
  struct fractal *fract_test =  fractal_new(name,size,size,1,1);

  int *matrix;
  matrix = (int *) malloc( size*size * sizeof(int));

  int k = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      fractal_set_value(fract_test,i,j,k);
      k++;
    }
  }

  for (int i = 0; i < size*size; i++) {
    CU_ASSERT_EQUAL(*(matrix+i),i);
  }
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
       (NULL == CU_add_test(pSuite, "Test get value",test_get_value))||
       (NULL == CU_add_test(pSuite, "Test set value",test_set_value))
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
