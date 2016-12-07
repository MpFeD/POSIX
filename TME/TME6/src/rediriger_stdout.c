#define _POSIX_SOURCE 1
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/types.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> 



void rediriger_stdout(char* nom_fichier){
  int fd1,fd2;
  fd1=open(nom_fichier,O_CREAT|O_TRUNC|O_RDWR);
  if(fd1==-1){
    printf("Erreur fichier");
    return;
  }
  chmod(nom_fichier,S_IRUSR|S_IWUSR);
  dup2(fd1,STDOUT_FILENO);
}


void restaurer_stdout(){
  int fd1;
  fd1=open("/dev/tty",O_RDWR);
  if(fd1==-1){
    printf("Erreur fichier");
    return;
  } 
  dup2(fd1,STDOUT_FILENO);
}

int main (int argc,char* argv[]) {
  printf("avant la redirection \n") ;
  rediriger_stdout("fichier.out") ;
  printf("après la redirection \n") ;
  restaurer_stdout() ;
  printf("après avoir restauré stdout \n") ;
  return EXIT_SUCCESS;
}
