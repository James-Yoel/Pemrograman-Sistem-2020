#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define bufSize 100

void producer();
void consumer();
int buf[bufSize];
int in = 0;
int out = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
  pthread_t prod, cons;
  int ret;
  //Inisialiasi semaphore empty dan full
  sem_init(&empty, 1, bufSize);
  sem_init(&full, 1, 0);;
  
  //Pembuatan thread prod yang menjalankan void producer
  ret = pthread_create(&prod, NULL, (void *)producer, NULL);
  //Error Handling
  if(ret){
    perror("pthread_create: producer");
    exit(EXIT_FAILURE);
  }
  //Pembuatan thread cons yang menjalankan void consumer
  ret = pthread_create(&cons, NULL, (void *)consumer, NULL);
  //Error Handling
  if(ret){
    perror("pthread_create: consumer");
    exit(EXIT_FAILURE);
  }
  //Sinkronisasi thread prod dan cons
  pthread_join(prod, NULL);
  pthread_join(cons, NULL);
  
  //Menghancurkan mutex, empty, dan full jika sudah tidak dipakai.
  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  //Selesai
  exit(EXIT_SUCCESS);
}

void producer(){
  int item = 0;
  //Non-stop
  while(1){
    //Pembuatan item (tidak melebih bufSize agar rapi)
    item = (item + 1) % bufSize;
    //Critical Region
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    //Memasukkann item kedalam buffer
    buf[in] = item;
    //Print hasil item yang dibuat, dan isi dari buf untuk mengecek apakah value sama
    printf("Producer: %d %d \n", item, buf[in]);
    //Increment in (tidak melebihi bufSize agar akses array tidak melebih batas)
    in = (in + 1) % bufSize;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    //Out Critical Region
    //Sleep agar output rapih
    sleep(1);
  }
}

void consumer(){
  int item;
  while(1){
    //Critical Region
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    //Mengambil isi dari buf
    item = buf[out];
    //Print hasil item yang diambil, dan isi dari buf untuk mengecek apakah value sama
    printf("Consumer: %d %d \n", item, buf[out]);
    //Increment out (tidak melebihi bufSize agar akses array tidak melebih batas)
    out = (out + 1) % bufSize;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    //Out Critical Region
    //Sleep agar output rapih
    sleep(1);
  }
}
