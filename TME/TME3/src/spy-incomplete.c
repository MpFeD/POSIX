/**** spy.c ****/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define _POSIX_SOURCE 1

#define BUFSZ 1024
#define WDSZ 24


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

    int or = 1, pid, command_size, i;
	char buf[BUFSZ];
	char *command[WDSZ];
	char multiple[100];

	while (or > 0) 
	  {
	    for (i = 0; i < BUFSZ ; i++)
	      buf[i] = '\0';
	    if ((or = read(STDIN_FILENO, buf, BUFSZ)) == -1)
	      perror("read");
	    else if (or > 0) {
	      command_size = cut_down(buf, (char**)command);
	      
	      printf("Nouvelle Commande :\n");
	      if(command_size == 1){
		if (fork()==0){
		  execlp(buf,buf ,NULL);
		  exit(0);
		}
		wait(NULL);
	      }else {
		if (fork()==0){
		  execvp(buf, command);
		  exit(0);
		}
		wait(NULL);
	      }
	    }
		
			
	  }
    
    return 0;
}
