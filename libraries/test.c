/*
 * Note: You must run this program like so:
 * LD_LIBRARY_PATH=. ./test
 */


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void test_fork() {
	pid_t pid = fork();
	assert(pid >= 0);
	if (pid == 0) {
		printf("all good in the hood\n");
		exit(42);
	} else {
		int status = 0;
		waitpid(pid, &status, 0);
		assert(WEXITSTATUS(status) == 42);
		printf("splines reticulated\n");
	}
}

void test_malloc() {
	void* mem = malloc(1024*sizeof(char));
	assert(mem != NULL);
}

void test_sleep() {
	sleep(1);
}

void test_exit() {
	exit(1);
}

int main() {
	test_exit();
	//test_malloc();
	//test_fork();
	return 0;
}

