#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void handle_sigint(int sig){
  exit(0);
}

int main(){
  signal(SIGINT, handle_sigint);
  while(1){
    printf("hello world\n");
    sleep(1);
  }
  return 0;
}
