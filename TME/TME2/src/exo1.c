#define _POSIX_SOURCE 1 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#define N_FILS 3



int main(int argc, char** argv){

  int i;
  pid_t pid;

  for(i=N_FILS; i>0; i--){
    if(fork()!=0){
      printf("Le fils %d s'arrete\n",getpid());
      break;
    }
  }

  return 0;
}
