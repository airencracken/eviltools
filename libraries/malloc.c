#include <stdlib.h>

#define __USE_GNU
#include <dlfcn.h>
#include "bashpipe.h"

static void* (*real)(size_t)=NULL;

void *malloc (size_t size) {
	if (real == NULL) {
		real = dlsym(RTLD_NEXT, "malloc");
	}

	start();
	return real(size);
}
