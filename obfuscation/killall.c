#include <stdio.h>

int main(int argc, char *argv[]){
	if (argc = 1){
		char *usage = "Usage: killall [OPTION]... [--] NAME...\n \
	killall -l, --list\n \
	killall -V, --version\n \
	\n \
	-e,--exact          require exact match for very long names\n \
	-I,--ignore-case    case insensitive process name match\n \
	-g,--process-group  kill process group instead of process\n \
	-y,--younger-than   kill processes younger than TIME\n \
	-o,--older-than     kill processes older than TIME\n \
	-i,--interactive    ask for confirmation before killing\n \
	-l,--list           list all known signal names\n \
	-q,--quiet          don't print complaints\n \
	-r,--regexp         interpret NAME as an extended regular expression\n \
	-s,--signal SIGNAL  send this signal instead of SIGTERM\n \
	-u,--user USER      kill only process(es) running as USER\n \
	-v,--verbose        report if the signal was successfully sent\n \
	-V,--version        display version information\n \
	-w,--wait           wait for processes to die\n";
		fprintf(stderr, "%s", usage);
		return 1;
	}

	return 0;
}
