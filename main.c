#include <stdio.h>
#include "dut.h"
#include "CUnit/Basic.h"

void simpleTest(void) {
        CU_ASSERT(2 == (1 + 1));
}

int main( int argc, const char* argv[] )
{
	printf( "\nTesting with CUnit\n\n" );
	int a = funca(5);
	   CU_pSuite pSuite = NULL;

	        /* initialize the CUnit test registry */
	   if (CUE_SUCCESS != CU_initialize_registry())
	      return CU_get_error();

	   /* add a suite to the registry */
	   pSuite = CU_add_suite("Suite_1", NULL, NULL);
	   if (NULL == pSuite) {
	      CU_cleanup_registry();
	      return CU_get_error();
	   }

	   /* add the tests to the suite */
	   if (NULL == CU_add_test(pSuite, "Simple Addition Test", simpleTest)) {
	      CU_cleanup_registry();
	      return CU_get_error();
	   }

	   /* Run all tests using the CUnit Basic interface */
	   CU_basic_set_mode(CU_BRM_VERBOSE);
	   CU_basic_run_tests();
	   CU_cleanup_registry();
	   return CU_get_error();
}
