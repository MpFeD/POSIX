#define _POSIX_SOURCE 1
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MAX_INTR 3

//Compte le nombre de signaux
//Se termine apres MAX_INTR SIGINT

sigset_t sig;
struct sigaction sigact;
int tab[32][2];
int i, j, total;

void sig_hand(int sig){
  for (i=0;i<32;i++){
    if (tab[i][0]==sig){
      tab[i][1]++;
      total++;
    }
  }
}

int main(int argc, char** argv){
  i=0;
  j=0;
  total=0;
  for (i=1; i<33;i++){
    tab[i][0]=i;
    tab[i][1]=0;
  }

  sigemptyset (&sig);
  sigprocmask (SIG_SETMASK, &sig, NULL);
  sigact.sa_mask = sig;
  sigact.sa_flags = 0;
  sigact.sa_handler = sig_hand;
  for (i=1;i<33;i++)
    sigaction (i, &sigact, NULL);

  while(1)
    if (tab[2][1]== MAX_INTR)
      break;

  printf("\nAffichage tableau finale :\n");
  for(i=1;i<33;i++){
    if(tab[i][1]!=0){
      printf("Le signal %d a été reçue %d fois\n",tab[i][0], tab[i][1]);
    }
  }
  printf("Nombre total de signaux : %d\nFin\n",total);
 
  return 0;
}
