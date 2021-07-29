#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signalHandler(int sig){
  printf("\nGood Bye !\n");
  //Exit
  exit(0);
}

int main(){
  int childPid, input, killed = 0;
  //Membuat child process dan jika benar child process
  if((childPid = fork()) == 0){
    //Print ID child process
    printf("Child %d\n", getpid());
    //Berjalan terus sampai di kill
    while(1);
  }
  //Print ID parent process
  printf("Parent %d\n", getpid());
  //Agar rapih
  sleep(1);
  //Menu untuk kill
  printf("Kill Process:\n");
  printf("1. Parent\n");
  printf("2. Child\n");
  //Looping sampai user input dengan sesuai
  do{
    printf("Input number to kill: ");
    scanf("%d", &input);
    if(input == 1){
      //Kill Parent Process
      kill(getpid(), SIGKILL);
      printf("Parent Process %d is Killed !\n", getpid());
      killed = 1;
    }
    else if(input == 2){
      //Kill Child Process
      kill(childPid, SIGKILL);
      //Mencegah child yang di kill menjadi zombie
      signal(SIGCHLD, SIG_IGN);
      printf("Child Process %d is killed !\n", childPid);
      killed = 1;
    }
    else{
      //Jika salah input
      printf("Wrong Input ! Retry...\n");
    }
  }
  while(killed != 1);
  printf("Type CTRL+C to exit...\n");
  //CTRL+C masuk kedalam handler
  signal(SIGINT, signalHandler);
  //Looping sampai CTRL+C
  while(1);
}
