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


int main (int argc, char** argv){
  char buffer[S_BUF];
  int fd_read,n;
  while(( fd_read = open ("multi.tmp", O_RDONLY)) == -1) {
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

  close(fd_read);

  unlink("multi.tmp");

  return 0;

}
