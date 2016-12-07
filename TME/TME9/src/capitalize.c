
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

#define N 1

char *shared;
int main (int argc, char** argv){

  int c;
  int shm_fd,pid,i;
  char buf1[1024],buf2;
  shm_fd = shm_open ("abc", O_RDWR | O_CREAT | O_TRUNC, 0777);

  ftruncate(shm_fd, 1024);

  shared = mmap (NULL ,1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, shm_fd ,0);
  sem_t *smutex = mmap (NULL ,sizeof(smutex), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1 ,0);

  sem_t *smutex2 = mmap (NULL ,sizeof(smutex), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1 ,0);

  sem_init(smutex,1,0);
  sem_init(smutex2,1,0);
 

  if (fork()==0){
    while(1){
      read(STDIN_FILENO,shared,1);
      if(*shared== '\n')
	*shared='\0';

      sem_post(smutex); //V 


      sem_wait(smutex2); //p 	 
      }
  }
 
  
  else {   
    while(1){ 
      sem_wait(smutex); //P
      buf2= toupper(*shared);
      printf("%c\n",buf2);
      sem_post(smutex2); //V
      }
  } 
  
  sem_destroy(smutex);
  
  
  return 0;

}

