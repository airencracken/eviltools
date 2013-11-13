#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define __USE_GNU
#include <dlfcn.h>

static pid_t (*real)()=NULL;

pid_t fork () {
	if (real == NULL) {
		real = dlsym(RTLD_NEXT, "fork");
	}

	printf("fork yeah\n");
	return real();
}
