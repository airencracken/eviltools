#include <stdio.h>

int main(int argc, char *argv[]){
	if (argc = 1){
		fprintf(stderr, "pkill: no matching criteria specified\nTry `pkill --help' for more information.\n");
		return 1;
	}

	return 0;
}
