#define _POSIX_SOURCE 1

#include "../include/ficindex_enonce.h"


int t[8] = {-2,-2,-2,-2,-2,-2,-2,-2}; //Tableau des descripteurs


/* *** indclose *** */ 
int indclose(int fd){
  if (t[fd]==-2) //Descripteur existe pas
    return -1;

  return close(fd);
}


/* *** indread *** */ 
ssize_t indread(int fd, void *buf, size_t nbytes){
  int ind;
  
  off_t cur_off = lseek(fd, 0, SEEK_CUR);

  if (t[fd] == -2) //Descripteur n'existe pas
    return -1;
  
  if(lseek(fd, 0, SEEK_SET)==-1) //Erreur Déplacement
    return -1;
  
  read(fd, &ind, sizeof(int));
  
  if(lseek(fd,cur_off,SEEK_SET)==-1) //Erreur Déplacement
    return -1;
  
  if (nbytes < ind) //Condition nbytes
    return -1;
  
  return read(fd,buf,ind);
}



/* *** indwrite *** */ 
ssize_t indwrite(int fd, const void *buf, size_t nbytes){
  int ind;
  off_t cur_off = lseek(fd, 0, SEEK_CUR);
  
  if (t[fd] == -2) //Descripteur n'existe pas
    return -1;
  
  if(lseek(fd, 0, SEEK_SET)==-1) //Erreur Déplacement 
    return -1;
  
  read(fd, &ind, sizeof(int));
  
  if(lseek(fd,cur_off,SEEK_SET)==-1) //Erreur Déplacement
    return -1;
  
  if (nbytes < ind) //Condition nbytes
    return -1;
  
  return write(fd,buf,ind);
}




/* *** indlseek *** */ 
off_t indlseek(int fd, off_t offset, int whence){ 
  //whence = positon initiale  
  off_t off = lseek(fd, 0, SEEK_CUR);
  int ind; 
    
  if (t[fd] == -2) //Descripteur n'existe pas
    return -1;

  if(lseek(fd, 0, SEEK_SET)==-1) //Erreur déplacement
    return -1;
  
  read(fd, &ind, sizeof(int));
  
  if(lseek(fd, off, SEEK_SET) == -1 )  //Erreur Déplacement
    return -1;
  
  offset *= ind;
  
  if(whence == SEEK_SET) //Debut de fichier 
    offset += sizeof(int);
  
  return lseek(fd,offset,whence);
}




/* *** indsearch *** */ 
void *indsearch(int fd, int (*cmp)(void *, void *), void *key){
  int ind,a;
  off_t off = lseek(fd, 0, SEEK_CUR);
  void *m;
 
  if (t[fd] == -2) //Descripteur n'existe pas
    return NULL;
  
  if(lseek(fd, 0, SEEK_SET) == -1) //Erreur déplacement
    return NULL;
 
  read(fd, &ind, sizeof(int));
  m = malloc(ind); 
  
  if(lseek(fd, off, SEEK_SET) == -1) //Erreur déplacement
    return NULL;
  
  while((a = read(fd, m, ind)) != 0){ //Lecture
    if(a == -1) //Erreur lecture
      return NULL;
    if(cmp(m, key) == 1) //Comparaison (mot, clé) est juste
      return m;  
  }
  
  return NULL; 
}




/* *** indxchg *** */
int indxchg(char *oldfic, char *newfic, unsigned int newind){

}




/* *** indopen *** */ 
int indopen(const char *path, int flags, int ind, mode_t mode){
  int fd2;
 
  if((fd2=open(path, flags, mode))==-1) //Erreur open
    return -1;
  
  if(read(fd2, &ind, sizeof(int))==0){ //Premier read
    t[fd2]=ind;
    write(fd2, &ind, sizeof(int));
  }
  return fd2;
}

 


