#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU
#include <dlfcn.h>

static void* (*real)(size_t)=NULL;

void *malloc (size_t size) {
	if (real == NULL) {
		real = dlsym(RTLD_NEXT, "malloc");
	}

	printf("fuck yeah\n");
	return real(size);
}
