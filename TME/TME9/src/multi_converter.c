#include "../include/converters.h"
#include <stdlib.h>
#include <stdio.h> 
#include <sys/mman.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <mqueue.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <semaphore.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

#define S_BUF 100


sigset_t sig_proc; 
struct sigaction action;
int sig; 
sigjmp_buf env;
char e[100];
char *shared;

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

char* display_results2(conversion_message request, results_array results) {
  int i;
  char d[100];
  sprintf(e,"Conversion for: %s %.3f\n", request.currency, request.amount);
  for(i = 0; i < NB_CONVERTERS; i++){
    sprintf(d,"\t %s %.3f \n", results[i].currency, results[i].amount);
    strcat(e, d);
  }
  return e;
}



void sig_hand(int sig){
  siglongjmp (env,sig);
}


int main (int argc, char** argv){


  sigfillset(&sig_proc); 
  sigdelset(&sig_proc,SIGINT);
  sigprocmask(SIG_SETMASK, &sig_proc, NULL);

  action.sa_mask=sig_proc; 
  action.sa_flags=0; 
  action.sa_handler = sig_hand; 
  sigaction(SIGINT, &action,NULL);
  
  int i=0,n,total=0,fd_write, shm_fd,j=0,k=0;
  int tubeDesc[2];
  char buffer[S_BUF],c[S_BUF], a1[S_BUF], a2[S_BUF],ret[S_BUF]={'\0'};
  sem_t *smutex;
  sem_t *smutex2;

  shm_fd = shm_open (argv[1], O_RDWR | O_CREAT, 0777);
  ftruncate(shm_fd, 1024);
  shared = mmap (NULL ,1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd ,0);


  if(argc != 2){
    printf("Erreur argument");
    return EXIT_FAILURE;
  }  

  
  printf("\n\n*****\nAttention le server doit être arrêter par l'envoi d'un signal SIGINT (Ctrl-C)\n*****\n\n");


  while(1){

    if((sig =sigsetjmp (env,1)) == SIGINT)
      break;
    

    
    if ((smutex = sem_open("abc", O_CREAT |O_EXCL | O_RDWR , 0777, 0)) == SEM_FAILED) {
      // Semaphore deja créé, ouvrir sans O_CREAT 
      smutex = sem_open("abc", O_RDWR);
    }
    
    if ((smutex2 = sem_open("def", O_CREAT |O_EXCL | O_RDWR , 0777, 0)) == SEM_FAILED) {
      // Semaphore deja créé, ouvrir sans O_CREAT 
      smutex2 = sem_open("def", O_RDWR);
    }
    
    
    sem_wait(smutex);
    strcpy(a1, shared);
    sem_post(smutex2);
    sem_wait(smutex);
    strcpy(a2, shared);

    i=0;
    while(i < NB_CONVERTERS){
      if (fork()==0){
	sprintf(shared,"\t %f %s\n",convert(a1,determine_currency(i),(atof(a2))),determine_currency(i));
	exit(0);
      }
      wait();
      j=0;
      k=0;
      while(ret[k]!='\0')
	k++;
      while(shared[j]!='\0'){
	ret[k]=shared[j];
	j++;
	k++;
      }
      i++;
    }
    
    strcpy(shared,ret);
    k=0;
    while(ret[k]!='\0'){
      ret[k]='\0';
      k++;
    }
    sem_post(smutex2);
    
  }

  printf("Arrêt du server...\n");

  munmap(shared, 1024);
  shm_unlink(argv[1]);
  sem_close(smutex);
  sem_close(smutex2);

  sem_unlink("abc");
  sem_unlink("def");
  

  return 0;

}



