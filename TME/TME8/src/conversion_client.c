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

char e[100];

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

int n;
char buffer[S_BUF]; 


int main (int argc, char** argv){
  int fd_read, fd_write;

  if (argc != 5){
    printf ("Erreur nb argument");
    return -1;
  }

 if (mkfifo(argv[2], S_IRUSR|S_IWUSR) == -1) {
    perror ("mkfifo");
    exit (1);
  }
  if (( fd_write = open (argv[2], O_WRONLY)) == -1) {
    perror ("open");
    exit (2);
  } 
  
  char s[S_BUF];
  char s2[S_BUF];
  sprintf (s,"%s",argv[3]);
  sprintf (s2," %s",argv[4]);
  strcat(s,s2);

  if (( n= write(fd_write,s, 50)) == -1) {
    perror ("write");
    exit (3);
  }

  while(( fd_read = open (argv[1], O_RDONLY)) == -1) {
    sleep(1);
  }		       

if (( n= read (fd_read, buffer, S_BUF)) == -1){
  perror ("read");
  exit (2);
 }
 else {
   buffer[n] = '\0';
   printf ("%s\n",buffer);
  }
  close (fd_read); 

  unlink(argv[2]);
  
  return 0;

}
