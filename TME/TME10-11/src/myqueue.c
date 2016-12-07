#define _XOPEN_SOURCE 700
#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <myqueue.h>


struct mq_attr *attrs[50];
sem_t *sr;
sem_t *sw;
sem_t *m;


char swrite[32] = "write";
char sread[32] = "read";

mqd_t mq_open(const char *nom, int mq_flags, int mode){
  int fd;

  if((m = sem_open("mutex",O_CREAT|O_RDWR,S_IRWXU,1)) == SEM_FAILED)
    if(errno == EEXIST)
      m = sem_open("mutex", O_RDWR);

  sem_wait(m);
 
  if((fd = shm_open(nom, mq_flags, mode))==-1)
    return -1;
 
  if((mq_flags & O_CREAT) == O_CREAT)
    if(ftruncate(fd,sizeof(struct mq_attr))==-1)
      return -1;
    
  attrs[fd] = mmap(NULL, sizeof(struct mq_attr), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  attrs[fd]->mq_curmsgs = 0;
  attrs[fd]->mq_maxmsg = 32;
  attrs[fd]->mq_flags = mq_flags;
  attrs[fd]->mq_msgsize = sizeof(msg_data);
  strcpy(attrs[fd]->blocked_writers,swrite);
  strcpy(attrs[fd]->blocked_readers,sread);
  attrs[fd]->nb_blocked_writers = 0;
  attrs[fd]->nb_blocked_readers = 0;
  attrs[fd]->subscriber = -1;
  attrs[fd]->notification_sig = -1;

  if((sr = sem_open(attrs[fd]->blocked_readers,O_CREAT|O_RDWR,S_IRWXU,0)) == SEM_FAILED)
    if(errno == EEXIST)
      sr = sem_open(attrs[fd]->blocked_readers, O_RDWR);  
  
  if((sw = sem_open(attrs[fd]->blocked_writers,O_CREAT|O_RDWR,S_IRWXU,0)) == SEM_FAILED)
    if(errno == EEXIST)
      sw = sem_open(attrs[fd]->blocked_writers, O_RDWR);

  sem_post(m);
  return fd;
}


int mq_close(mqd_t mqdes){
  sem_close(sr);
  sem_close(sw);
  sem_close(m);
  return munmap(attrs[mqdes], sizeof(struct mq_attr));
}

int mq_unlink(const char* name){
  sem_unlink(sread);
  sem_unlink(swrite);
  sem_unlink("mutex");
  return shm_unlink(name);
}

int mq_setattr(mqd_t mqdes, struct mq_attr * mqstat, struct mq_attr * omqstat){
  
  sem_wait(m);
  bcopy(attrs[mqdes], omqstat, sizeof(struct mq_attr));
  attrs[mqdes]->mq_flags = mqstat->mq_flags;
  sem_post(m);
  return 0;
}

int mq_getattr(mqd_t mqdes, struct mq_attr *mqstat ){
  mqstat = attrs[mqdes];
  return 0;
}

int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio){
  if(msg_len > attrs[mqdes]->mq_msgsize)//msg_len > mq_msgsize
    return -1;
  
  if(msg_prio > 32)//priorité < 32
    return -1;

  if(attrs[mqdes]->mq_curmsgs == attrs[mqdes]->mq_maxmsg){
    if((attrs[mqdes]->mq_flags&O_NONBLOCK) != O_NONBLOCK){
      attrs[mqdes]->nb_blocked_writers++;
      sem_wait(sw);
      attrs[mqdes]->nb_blocked_writers--;
    }else//file pleine
      return -1;
    
  }else{
    if(attrs[mqdes]->subscriber>0){
      kill(attrs[mqdes]->subscriber, attrs[mqdes]->notification_sig);
      attrs[mqdes]->subscriber = -1;
      attrs[mqdes]->notification_sig = -1;
      sem_post(sr);
    }else if(attrs[mqdes]->mq_curmsgs != 0 && attrs[mqdes]->nb_blocked_readers>0)
      sem_post(sr);
  }
  
  strncpy(attrs[mqdes]->queue[attrs[mqdes]->mq_curmsgs].data, msg_ptr, msg_len);
  attrs[mqdes]->queue[attrs[mqdes]->mq_curmsgs].prio = msg_prio;
  attrs[mqdes]->queue[attrs[mqdes]->mq_curmsgs].length = msg_len;
  attrs[mqdes]->mq_curmsgs++;
  
  return 0;
}

ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio){
  
  if(msg_len > attrs[mqdes]->mq_msgsize)//message trop long
    return -1;
  
  if(attrs[mqdes]->mq_curmsgs == 0){
    if((attrs[mqdes]->mq_flags&O_NONBLOCK) != O_NONBLOCK){
      attrs[mqdes]->nb_blocked_readers++;
      sem_wait(sr);
      attrs[mqdes]->nb_blocked_readers--;
    }else//file vide
      return -1;
  }else{
    if(attrs[mqdes]->mq_curmsgs != attrs[mqdes]->mq_maxmsg && attrs[mqdes]->nb_blocked_writers>0)
      sem_post(sw);
  } 
  strncpy(msg_ptr, attrs[mqdes]->queue[0].data, attrs[mqdes]->queue[0].length);
  msg_prio[0] = attrs[mqdes]->queue[0].prio;

  int i;
  for (i=0;i< attrs[mqdes]->mq_curmsgs -1;i++)
    attrs[mqdes]->queue[i] =attrs[mqdes]->queue[i+1]; 
  attrs[mqdes]->mq_curmsgs--;
  return attrs[mqdes]->queue[0].length;
}


 
mqd_t mq_notify(mqd_t mqdes, const struct sigevent *notification){
  pid_t pidsub = attrs[mqdes]->subscriber;
  int notify = notification->sigev_notify;
  
  if(notify != SIGEV_NONE && notify != SIGEV_SIGNAL && notify != SIGEV_THREAD)//sigev_notify non permis
    return -1;
  
  if(pidsub == getpid() && notification == NULL){
    attrs[mqdes]->subscriber = -1;
    attrs[mqdes]->notification_sig = -1;
    return 0;
  }
  
  if(pidsub > 0)//proc deja enregistré pour recevoir les notifications de cette file de messages.
    return -1;

  attrs[mqdes]->notification_sig = notification->sigev_signo;
  attrs[mqdes]->subscriber = getpid();

  return 0;
}

