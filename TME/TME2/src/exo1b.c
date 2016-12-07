#define _POSIX_SOURCE 1 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#define N_FILS 3

void f_nfils(int n){
  if (fork()==0 || n==1){
    /*la fonction printf est appelee 4 fois car le pere l'execute aussi mais 3 fils sont bien crees*/
    printf("Le fils %d s'arrete\n",getpid());
    return;
  }

  else {
     
     f_nfils(n-1);
  }
}

int main(int argc, char** argv){
 
    pid_t pid;

  f_nfils(N_FILS);

  return 0;
}
