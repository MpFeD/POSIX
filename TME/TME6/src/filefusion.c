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

  
  if (argc !=4){
    printf("Erreur 3 arguments requis\n\n");
    return -1;
  }

  int fd1,fd2,fd3; 
  fd1=open(argv[1],O_RDONLY);
  fd2=open(argv[2],O_RDONLY);
  fd3=(open(argv[3],O_CREAT|O_TRUNC|O_RDWR));
  
  if (fd1==-1){
    printf("Erreur premier argument\nVeuillez choisir un fichier valide\n\n");
    return -1;
  }

   if (fd2 ==-1){
    printf("Erreur deuxieme argument\nVeuillez choisir un fichier valide\n\n");
    return -1;
    }

  
   if (fd3==-1){
  printf("Erreur 3eme argument \n\n");
  return -1;
  }

 char c; 
 int a=1,b=1;


 while (1){
   
   while(a=read(fd1,&c,1)){
  
     write(fd3,&c,1);
     if(c==' ')
       break;
   }
   while(b=read(fd2,&c,1)){ 
     
     write(fd3,&c,1);
     if(c==' ')
       break;
   }
   
   if (a==0 && b==0)
     break;
   
 }

  return 0;
}
