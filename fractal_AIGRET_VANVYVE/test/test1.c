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
// Test si alloc passe bien à 0 apres myfree
void test_myfree_desalloc(void)
{
  int* pointeurtest = (int *) mymalloc(sizeof(int));
  block_header *bh_test = (block_header *)(pointeurtest-1);
  myfree(pointeurtest);
  CU_ASSERT_EQUAL((bh_test->alloc),0);
}
*/


int setup(void)  { return 0; }
int teardown(void) { return 0; }

int main()
{
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Projet-Fractales", setup, teardown);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
/*
   if ((NULL == CU_add_test(pSuite, "Myfree desalloc",test_myfree_desalloc)) ||
       (NULL == CU_add_test(pSuite, "Mycalloc initialisation",test_mycalloc_init))
     )
   {
     CU_cleanup_registry();
     return CU_get_error();
   }
*/

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   CU_cleanup_registry();
   return CU_get_error();
}
