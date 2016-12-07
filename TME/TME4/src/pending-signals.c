#define _POSIX_SOURCE 1
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


sigset_t sig;
struct sigaction sigact;

int main (int argc,char** argv){

  sigemptyset (&sig);
  sigaddset(&sig, SIGINT);
  sigaddset(&sig, SIGQUIT);
  sigprocmask (SIG_SETMASK, &sig, NULL);

  /*Pour la question de l'exo 3 :
    sigdelset(&sig, SIGINT);
    sigdelset(&sig, SIGQUIT);*/


  sleep(5);

  sigpending(&sig);

  

  if (sigismember(&sig,SIGINT))
    printf ("SIGINT pendant\n");
  if (sigismember(&sig,SIGQUIT))
    printf ("SIGQUIT pendant\n");
 
  printf("Fin\n");

  return 0;
}
