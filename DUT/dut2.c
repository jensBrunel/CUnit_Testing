#include <stdio.h>
#include "dut2.h"

int funcb(int b)
{
    malloc(b);
	free(b);
	return b;
}
