#include <stdio.h>
#include <stdlib.h>
#define _POSIX_SOURCE 1 
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>
#define N 5

int main (int argc, char** argv){
  pid_t pid;
  pid=getpid();
  //char c[100];
  
  if (argc != 2){
    printf("Erreur un argument est requis\n");
    return 1;
  }

  if ((atoi(argv[1]))==5){
    printf("Fin du programme\n");
    return 0;
    }

  if ((atoi(argv[1]))>5){
    printf("La valeur ne doit pas dépasser 5\n");
    return 0;
    }
  //printf("XXX=%s\n",argv[0]);

  int i=atoi(argv[1]);
  i++;
  printf("PID=%d\n",getpid());
  printf("%d\n",i);
  char j = (char)(((int)'0')+i);
  char k[0]="";
  k[0]=j;
  execl("./bin/exo4", "./exo4",k,NULL);
  wait(NULL);

  return 0;
}
