#define _POSIX_SOURCE 1 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#define N_FILS 3



void wait_1_fils(){

  int i;
 for(i=N_FILS; i>0; i--){
    if(fork()==0){
      printf("Le fils %d s'arrete\n",getpid());
      return;
    }
  }
 printf("le pere attend\n");
 wait(NULL);
}


void wait_N_fils(){

  int i;

 for(i=N_FILS; i>0; i--){
    if(fork()==0){
      printf("Le fils %d s'arrete\n",getpid());
      return;
    }
  }


 for(i = N_FILS; i>0; i--){
   printf("le pere attend\n");
   wait(NULL);
 }
}


void wait_last_fils(){

  int i;
  pid_t pid;
  pid_t pid_t[3];

 for(i=N_FILS; i>0; i--){
   if((pid=fork())==0){
     if (i==1){
       printf("Le processus %d est le dernier fils\n",getpid());
     } 
      printf("Le fils %d s'arrete\n",getpid());
      return;
    }
   pid_t[i-1]=pid;
  }

printf("Le pere attend le pid %d\n",pid_t[0]);
waitpid(pid_t[0]);

}

int main(int argc, char** argv){

  //wait_1_fils();
  //wait_N_fils();
  wait_last_fils();
  return 0;
}
