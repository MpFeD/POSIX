#include "../include/converters.h"
#include <string.h>
#define _POSIX_SOURCE 1
#include <sys/wait.h> 
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h> 
#define S_BUF 100

sigset_t sig_proc; 
struct sigaction action;
int nbsig = 0;

/* Converts from any to EUR */
double convertfrom(char* input_currency, double input_amount) {
	if (strcmp(input_currency, "GBP") == 0)
		return (input_amount / GBP);
	else if (strcmp(input_currency, "USD") == 0)
		return (input_amount / USD);
	else if (strcmp(input_currency, "JPY") == 0)
		return (input_amount / JPY);
	else if (strcmp(input_currency, "CNY") == 0)
		return (input_amount / CNY);
	else if (strcmp(input_currency, "EUR") == 0)
		return input_amount;
	else {
		perror("Unknown currency");
		exit(1);
	}
}


/* Converts from EUR to any */
double convertto(char* target_currency, double input_amount) {
	if (strcmp(target_currency, "GBP") == 0)
		return (input_amount * GBP);
	else if (strcmp(target_currency, "USD") == 0)
		return (input_amount * USD);
	else if (strcmp(target_currency, "JPY") == 0)
		return (input_amount * JPY);
	else if (strcmp(target_currency, "CNY") == 0)
		return (input_amount * CNY);
	else if (strcmp(target_currency, "EUR") == 0)
		return input_amount;
	else {
		perror("Unknown currency");
		exit(1);
	}
}


/* Converts from any to any */
double convert(char* input_currency, char* target_currency, double input_amount) {
	return convertto(target_currency, convertfrom(input_currency, input_amount));
}


/* Determines a currency string identifier, given its integer identifier */
char* determine_currency(int curr_nb) {
	switch(curr_nb) {
		case EUR_CONV: return "EUR";
		case GBP_CONV: return "GBP";
		case USD_CONV: return "USD";
		case JPY_CONV: return "JPY";
		case CNY_CONV: return "CNY";
		default: perror("Unknown currency"); exit(1);
	}
}


/* Processes a conversion request */
void handle_conversion_request(conversion_message request, conversion_message *result, int curr_nb) {
	result->pid_sender = getpid();
	strcpy(result->currency, determine_currency(curr_nb));
	result->amount = convert(request.currency, result->currency, request.amount);
}
	

/* Displays the contents of a conversion results message */
void display_results(conversion_message request, results_array results) {
	int i;
	printf("Conversion for: %s %.3f\n", request.currency, request.amount);
	for(i = 0; i < NB_CONVERTERS; i++)
		printf("\t %s %.3f\n", results[i].currency, results[i].amount);
}




void sig_hand(int sig){ 
  nbsig++;
}


int main (int argc, char** argv){

  int i=0,n,total=0,fd_write;
  int tubeDesc[2];
  char buffer[S_BUF],c[S_BUF],ret[S_BUF]={'\0'};

  sigfillset(&sig_proc); 
  action.sa_mask=sig_proc; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand; 
  sigdelset(&sig_proc,SIGUSR1); 
  sigdelset(&sig_proc,SIGINT); 
  sigprocmask(SIG_SETMASK, &sig_proc, NULL);
  sigaction(SIGUSR1, &action, NULL);


  if (pipe (tubeDesc) == -1) {
    perror ("pipe"); 
    exit (1);
  } 

  if(argc != 3){
    printf("Erreur argument");
    return EXIT_FAILURE;
  }

  while(i < NB_CONVERTERS){
    if (fork()==0){
      close (tubeDesc[0]); 
      sprintf(c,"\t %3.f %s\n",convert(argv[1],determine_currency(i),(double)(atoi(argv[2]))),determine_currency(i));
      if ((n=write(tubeDesc[1], c, S_BUF) == -1)) {
	perror ("write");
	exit (3);
      }
      kill(getppid(),SIGUSR1);
      exit(0);
    }
    sleep(1);
    i++;
  }
  
  while(nbsig<NB_CONVERTERS)
    sleep(1);

  sprintf(ret,"Converting %s %s\n", argv[1], argv[2]);

  i=0;
  while (ret[i]!='\0'){
    total++;
    i++;
  }
  
  close(tubeDesc[1]);
  for(i=0; i<NB_CONVERTERS; i++){
    if ((n=read (tubeDesc[0], buffer, S_BUF)) == -1){
      perror ("read"); 
      exit (3);
    }
    total+=n;
    strcat(ret,buffer);
  }
  ret[total] = '\0'; 
 
  if (mkfifo("multi.tmp", S_IRUSR|S_IWUSR|O_NONBLOCK) == -1) {
    perror ("mkfifo");
    exit (1);
  }

  if ((fd_write = open("multi.tmp", O_WRONLY)) == -1) {
    perror ("open");
    exit (2);
  } 
  if (( n= write(fd_write,ret, total)) == -1) {
    perror ("write");
    exit (3);
  }
  close(fd_write);

  return 0;

}



