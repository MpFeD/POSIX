/**** decoder.c ****/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include <decoder.h>


#define _XOPEN_SOURCE 700


int magicsq[3][3] = {{4, -1, 8}, {-1, -1, -1}, {2, -1, 6}};


int check() {
	int i, j, sums[8];
	for (i = 0; i < 8; i++) 
		sums[i] = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sums[i] += magicsq[i][j];
			sums[i+3] += magicsq[j][i];
			if (i == j) sums[6] += magicsq[i][j];
			if ((i+j) == 2) sums[7] += magicsq[i][j];
		}
	}
	int result = 1;
	i = 1;
	while ((i < 8) && (result == 1)) {
		if (sums[0] != sums[i])
			result = 0;
		i++;
	}
	return result;
}


void display() {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("  %d", magicsq[i][j]);
		printf("\n");
	}
	printf("\n");
}


int solve(int x) {
  int i,j,k,l,m;
  for(i=0;i<10;i++){
     for(j=0;j<10;j++){ 
       for(k=0;k<10;k++){
	 for(l=0;l<10;l++){ 
	   for(m=0;m<10;m++){
	     if (fork()==0){
	       magicsq[0][1]=i;
	       magicsq[1][0]=j;     
	       magicsq[1][1]=k;	     
	       magicsq[1][2]=l;	     
	       magicsq[2][1]=m;	     
	       if (check()){
		 display();
		 exit(0);
	       }
	       exit(0);
	     }
	     wait(NULL);
	   }
	 }
       }
     }
  }
}

int main(int argc, char **argv)
{	
  solve(0);
  return 0;
}
