#define _POSIX_SOURCE 1 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>


int main (int arg, char* argv[]) {

  int i, j, p;

for (i=0; i<3 ; i++)
  if ((p=fork ()) == 0) {
    printf ("i=%d\n", i);
    j=0; 
    while (j<i && ((p=fork()) == 0))
      j++;
    if (p==0)
      printf("j=%d\n",j);
    if (p!=0)
      wait(NULL);
    exit(j);
  } /* if */


 return (0);

}
