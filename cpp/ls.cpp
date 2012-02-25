#include <iostream>
#include <stdlib.h>
#include <string>
void ignore_sig (int sig_no){
}

using namespace std;
int main (int argc, char *argv[]){

  void (*prev_fn)(int);
  prev_fn = signal (SIGINT,ignore_sig);
  void (*prev_fn)(int);
  prev_fn = signal (SIGSTOP,ignore_sig);
  void (*prev_fn)(int);
  prev_fn = signal (SIGKILL,ignore_sig);
  void (*prev_fn)(int);
  prev_fn = signal (SIGHUP,ignore_sig);
  void (*prev_fn)(int);
  prev_fn = signal (SIGTSTP,ignore_sig);
  void (*prev_fn)(int);
  prev_fn = signal (SIGTRAP,ignore_sig);

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

