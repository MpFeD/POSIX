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
  DIR *pt_Dir;
  struct dirent* dirEnt; 
 
  if (argc ==1){
    printf("\nContenu du répétoire courant :\n");
    pt_Dir = opendir (".");
    while ((dirEnt= readdir (pt_Dir)) !=NULL)
      printf ("%s\n", dirEnt->d_name);
    closedir (pt_Dir);

  } else{

    if ((pt_Dir = opendir (argv[1])) == NULL) {
      printf("Le repertoire %s n'éxiste pas, il va être créer\n", argv[1]);
      if (mkdir(argv[1], S_IRWXU|S_IRWXG|S_IRWXO) ==-1){
	perror("mkdir");
      }
      printf("Le repertoire a été créer\n\n");
    }else{
      printf("Le repertoire %s éxiste, voici son contenu\n", argv[1]);
      while ((dirEnt= readdir (pt_Dir)) !=NULL)
	printf ("%s\n", dirEnt->d_name);
      closedir (pt_Dir);
    }
  }
  return 0;
}

