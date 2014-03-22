#include <stdlib.h>

#define __USE_GNU
#include <dlfcn.h>

static void (*real)(int)=NULL;

void exit(int status) {
	if (real == NULL) {
		real = dlsym(RTLD_NEXT, "exit");
	}

	start();
	real(status);
}
