#define _POSIX_SOURCE 1
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


sigset_t sig;
struct sigaction sigact;
int i=0,j=0;


int main (int argc,char** argv){

  sigemptyset (&sig);
  sigaddset(&sig, SIGINT);
  sigaddset(&sig, SIGQUIT);

  sigprocmask (SIG_SETMASK, &sig, NULL);
  sigact.sa_mask = sig;
  sigact.sa_flags = 0;
  sigaction (SIGINT, &sigact, NULL);
  sigaction (SIGQUIT, &sigact, NULL);


  /*Pour la question de l'exo 5 :
  sigdelset(&sig, SIGINT);
  sigdelset(&sig, SIGQUIT);*/

  sleep(5); 
  
  sigpending(&sig);

  if (sigismember(&sig,SIGINT))
    i++;
  
  if (sigismember(&sig,SIGQUIT))
  j++;


  printf("Nombre de SIGINT :%d\nNombre de SIGQUIT : %d\nFin",i,j);
  
  return 0;
}
