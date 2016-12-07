/**** spy.c ****/
#define _POSIX_SOURCE 1
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define BUFSZ 1024
#define WDSZ 24

#define NBUF 3

sigset_t sig;
struct sigaction sigact;



void sig_hand(){
}




int cut_down(char *buf, char **cmd) {
	char* s = strtok(buf, " \n");
	int i = 0;
	while (s != NULL) {
		cmd[i] = (char*) malloc(sizeof(char) * WDSZ);
		strcpy(cmd[i], s);
		s = strtok(NULL, " \n");
		i++;
	}
	cmd[i] = NULL;
	return i;
}


int main(int argc, char **argv)
{

  int or = 1, command_size, i=0, total=0,j=0;
  char buf[BUFSZ];
  char *command[WDSZ];
  pid_t tab[NBUF];


  sigemptyset (&sig);
  sigprocmask (SIG_SETMASK, &sig, NULL);
  sigact.sa_mask = sig;
  sigact.sa_flags = 0;
  sigact.sa_handler = sig_hand;
  sigaction (SIGINT, &sigact, NULL);


    while (or > 0) {
      while(total!= NBUF){
	for (i = 0; i < BUFSZ ; i++)
	  buf[i] = '\0';
	if ((or = read(STDIN_FILENO, buf, BUFSZ)) == -1)
	  perror("read");
	if (or > 0) {

	  command_size = cut_down(buf, (char**)command);
	  
	  if(command_size == 1){
	    if ((tab[j]=fork())==0){
	      sigsuspend(&sig);
	      execlp(buf,buf ,NULL);
	      exit(0);
	    }
	  }else {
	    if ((tab[j]=fork())==0){
	      sigsuspend(&sig);
	      execvp(buf, command);
	      exit(0);
	    }
	  }
	  j++;
	  total++;
	}
	
      }
      sleep(1);
       for(j=0; j<NBUF; j++){
	 kill(tab[j], SIGINT);
       }
       for(j=0; j<NBUF; j++){
	 wait(NULL);
       }
       total=0;
       j=0;
    } 
  
    
    return 0;
}
