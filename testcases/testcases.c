#include <stdio.h>
#include "testcases.h"
#include "dut.h"

void simpleTest(void) {

        CU_ASSERT(2 == funca(2));
}

void setTestCases()
{
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
}
