#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
  key_t key = 1243;
  char buff[100], *str;
  int count;
  int i, id;

  if (fork()==0){
    if((id = shmget(key, sizeof(str), IPC_CREAT | 0666)) < 0){
	perror("shared memory not created");
	exit(1);
      }
      str = (char *) shmat(id, 0, 0);
      if(str<=(char *) (0)){
	perror("shared memory not attached");
	exit(1);
      }
      while(1){
	printf("Enter message!" );
	fgets(str, 100, stdin);
	sleep(1);
	printf("\n");
      }
  }
  else{
    sleep(5);
    if((id = shmget(key, sizeof(str), 0)) < 0){
      perror("shared memory not accessed ");
      exit(1);
    }
    str = (char *) shmat(id, 0, 0);
    if (str <= (char *) (0) ){
      perror("shared memory not attached");
      exit(1);
    }
    while(sizeof(str)>0){
      sleep(1);
      puts(str);
    }
  }
  return 0;
}