#define _POSIX_SOURCE 1
#include <sys/types.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <setjmp.h>
#define NFIN 5

sigset_t sig_proc; 
struct sigaction action;
int sig; 
sigjmp_buf env;

void sig_hand(int sig){
  siglongjmp (env,sig);
}

int main (int argc, char * argv[]) {
  int i = 0;
  
  action.sa_mask=sig_proc; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand; 
  sigaction(SIGINT, &action,NULL);
  sigaction(SIGALRM, &action,NULL);

  alarm(5);

  while (1){
    sig = sigsetjmp (env,1);
    if(sig == SIGALRM){
      printf("SIGALRM reçu \n");
      break;
      }
    if(sig == SIGINT){ 
      printf ("SIGINT reçu \n");
      i++;
      if (i==NFIN){
	break;
      }
    }
  }
  
  printf("Fin du programme\n");
  return 0;
  
}
