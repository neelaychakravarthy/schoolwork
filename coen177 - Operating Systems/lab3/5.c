#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <sys/wait.h>

int main(){
  int fds[2];
  char buff[100], *str;
  int count;
  int i;
  pipe(fds);

  if (fork()==0){
    printf("Enter message! ");
    fgets(str, 100, stdin);
    printf("\n");
    close(fds[0]);
    write(fds[1], str, strlen(str));
    exit(0);
  }

  else if(fork()==0){
    close(fds[1]);
    while((count=read(fds[0],buff,60))>0){
      for(i=0;i<count;i++){
	      write(1,buff+i,1);
      }
      printf("\n");
    }
    exit(0);
  }
  else{
    close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
  }
}