#define _POSIX_SOUCE 1
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_FILS 3
#define SIZE 40

int main (int argc, char** argv){

  int* tab=NULL;
  tab=(int*)calloc(SIZE,4);
  pid_t pid;


  int i, j;
  for(i=0;i<N_FILS;i++){
    if ((pid = fork())!=0){
      printf("Fils numéro %d crée, pid=%d\n",i,pid);
      break;
    }
    tab[i]=getpid();
    if(i == N_FILS-1){
      printf("\n**********\nTableau Final :\n");
      for(j=0;j<N_FILS;j++){
	printf("valeur=%d\n",tab[j]);
      }  
      exit(0);
    }
  }
  
  wait(NULL);

  return 0;

}
