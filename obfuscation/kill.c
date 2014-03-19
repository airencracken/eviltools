#include <stdio.h>

int main(int argc, char *argv[]){
	if (argc = 1){
		fprintf(stderr, "kill: usage: kill [-s sigspec | -n signum | -sigspec] pid | jobspec ... or kill -l [sigspec]\n");
		return 1;
	}

	return 0;
}
