#include <stdint.h>
#include "Stubs.h"
#include  <stdio.h>
#include <stdlib.h>

void *__real_malloc (size_t);

/* This function wraps the real malloc */
void * __wrap_malloc (size_t size)
{
    void *lptr = 0/*__real_malloc(size)*/;
    printf("Malloc: %d bytes %p\n", size, lptr);
    return lptr;
}

void __real_free(void *ptr);

void __wrap_free(void *ptr)
{
   printf("Free: %p address\n", ptr);
   //__real_free(ptr);
}