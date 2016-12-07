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
#define N 1

int main (int argc, char** argv){
  
  if (argc != 3){
    printf("Il faut deux arguments\n\n");
    return -1;
  }
  
  int fd1=open(argv[1],O_RDONLY);

  if (fd1==-1){
    printf("Erreur premier argument\nVeuillez choisir un fichier valide\n\n");
    return -1;
  }
  
  int j=0,nbmot=0, tab[100];
  char* mot;
  mot=calloc(25,sizeof(char));
  char a, c;
  
  for(j=0;j<100;j++)
    tab[j]=0;
  
  j=0;
  
  while (1){
    while(a=read(fd1,&c,1)){
      int d = (int)c;
      if (!((d<='z' && d>='a')||(d<='Z' && d>='A'))){ 
	if(strcmp (mot,argv[2])==0){
	  tab[nbmot]=lseek(fd1,0,SEEK_CUR)-strlen(mot);
	  nbmot++;
	}
	free(mot);
	mot=calloc(25,sizeof(char));
	j=0;
      }
      else{
	*(mot+j)=c;
	j++;
      }
    }
    if(a==0)
      break;
  }   
  printf("Le nombre d'occurences de %s est %d\n",argv[2], nbmot);
  
  if(nbmot>0){
    j=0;
    while(tab[j]!=0){
      printf("L'occurence numéro %d est située à la position %d\n",j+1,tab[j]);
      j++;
    }
  }


  return 0;
}
