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
#define S_BUF 100

char *shared;

int main (int argc, char** argv){
  char buffer[S_BUF];
  int shm_fd,n;
  sem_t *smutex, *smutex2;

  
  // smutex = sem_open("abc", O_RDWR);
  //  smutex2 = sem_open("def", O_RDWR);


if ((smutex = sem_open("abc", O_CREAT |O_EXCL | O_RDWR , 0777, 0)) == SEM_FAILED) {
  // Semaphore deja créé, ouvrir sans O_CREAT 
    smutex = sem_open("abc", O_RDWR);
    }

  if ((smutex2 = sem_open("def", O_CREAT |O_EXCL | O_RDWR , 0777, 0)) == SEM_FAILED) {
    // Semaphore deja créé, ouvrir sans O_CREAT 
    smutex2 = sem_open("def", O_RDWR);
  }


      if(argc != 4){
	printf("Erreur argument");
    return EXIT_FAILURE;
      }  

    
  shm_fd = shm_open (argv[1], O_RDWR | O_CREAT, 0777);
  ftruncate(shm_fd, 1024);
  shared = mmap (NULL ,1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd ,0);


  strcpy (shared, argv[2]);

  sem_post(smutex);
  sem_wait(smutex2);   
  
  strcpy (shared, argv[3]);
  sem_post(smutex);



  sem_wait(smutex2);
  printf("\n*******************************\n");


  printf("%s\n",shared);

  
  return 0;

}
