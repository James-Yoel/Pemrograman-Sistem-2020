#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void thread1();
void thread2();
int g1 = 0;

int main(){
  int i;
  pthread_t thrd1, thrd2;
  int ret;
  
  ret = pthread_create(&thrd1, NULL, (void *)thread1, NULL);
  if(ret){
    perror("pthread_create: thread1");
    exit(EXIT_FAILURE);
  }
  ret = pthread_create(&thrd2, NULL, (void *)thread2, NULL);
  if(ret){
    perror("pthread_create: thread2");
    exit(EXIT_FAILURE);
  }
  pthread_join(thrd2, NULL);
  pthread_join(thrd1, NULL);
  exit(EXIT_SUCCESS);
}

void thread1(){
  while(g1 < 5){
    printf("thread1: g1=%d\n", g1);
    g1++;
    //sleep(1);
  }
}

void thread2(){
  while(g1 < 5){
    printf("thread2: g1=%d\n", g1);
    g1++;
    //sleep(1);
  }
}
