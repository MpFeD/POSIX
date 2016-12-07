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

int main (int argc, char** argv){
  
  int i=0, fd1, fd2;
  char c,c2;
  struct stat s;

  if (argc < 3 || argc > 4){
    printf("Le nombre d'arguments doit être 2 ou 3\n");
    return -1;
  }

  while(argv[1][i] != '\0'){
    i++;
  }
  c=argv[1][0];
  
  if(i!=1 || c!='e' && c!='E' && c!='r' && c!= 'R' && c != 'C'&& c!= 'c'){
    printf ("Erreur premier argument\nVeuillez choisir E, e, R, r, C, c\n\n");
    return -1;
  }

  if (S_ISDIR (s.st_mode)){
    ("Le deuxieme argument ne doit pas être un repertoire");
    return -1;
  }

  if (fd1 =(open (argv[2],O_RDWR))==-1){
    printf("Erreur deuxieme argument\nVeuillez choisir un fichier valide\n\n");
    return -1;
  }

  

  if(c == 'E' || c=='e'){
    unlink(argv[2]);
    printf("Le fichier %s a été supprimer\n\n",argv[2]);
  }

  
  if(c == 'r' || c=='R'){
    if (argc != 4){
      printf ("Erreur 3 arguments requis\n\n");
      return -1;
    }
    rename(argv[2],argv[3]);
  }

  if (c== 'c' || c=='C'){
    if (argc != 4){
      printf ("Erreur 3 arguments requis\n\n");
      return -1;
    }
    char c2=argv[3][0];
    if(c2!='r' &&c2!='R' &&c2!='W' &&c2!='w'){
      printf ("Erreur 3eme arguments\nVeuillez choisir r, R, w, W\n\n");
      return -1;
    }
    if (c2 == 'r' || c2 == 'R'){
      chmod(argv[2],S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  
    }
    if (c2 == 'w' || c2 == 'W'){
      chmod(argv[2],S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  
    }
  }

  return 0;
}
