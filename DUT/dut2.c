#include <stdio.h>
#include <stdlib.h>
#include "dut2.h"

int funcb(int b)
{
    void * ptr = malloc(b);
	free(ptr);
	return b;
}
