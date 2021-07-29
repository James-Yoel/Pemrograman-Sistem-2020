#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

int main(){
  int child, shmid, shmid2, key=1000, key2=2000, *ptrData;
  //Inisialisasi Shared Memory
  shmid = shmget(key, sizeof(int), 0644 | IPC_CREAT);
  ptrData=(int*)shmat(shmid, (void*)0, 0);
  *ptrData=0;
  
  //Inisialisasi Semaphore
  sem_t *mutex;
  shmid2 = shmget(key2, sizeof(int), 0644 | IPC_CREAT);
  //Membuat mutex (nilai hanya boleh 0 atau 1)
  mutex = (sem_t *)shmat(shmid2, (void*) 0, 0);
  
  //Error Handling mutex
  if(sem_init(mutex, 1, 1) < 0){
    perror("Semaphore Initialization");
    exit(EXIT_FAILURE);
  }
  
  //Membuat proses child setelah segala inisialisasi selesai
  child=fork();
  
  //Jika child process
  if(child == 0){
    int i = 0;
    for(i = 0 ; i<15; i++){
      //Down Semaphore
      sem_wait(mutex);
      //Critical Region
      *ptrData = *ptrData+1;
      printf("i = %d child's ptrData = %d\n", i, *ptrData);
      //Up Semaphore
      sem_post(mutex);
    }
  }
  //Jika bukan child process
  else if(child > 0){
    int i = 0;
    for(i = 0; i<15; i++){
      //Down Semaphore
      sem_wait(mutex);
      //Critical Region
      *ptrData = *ptrData+1;
      printf("i = %d parent's ptrData = %d\n", i, *ptrData);
      //Up Semaphore
      sem_post(mutex);
    }
    //Menunggu proses child selesai
    int status;
    waitpid(child, &status, 0);
  }
  //Melepas shared memory jika sudah tidak dipakai
  shmdt(ptrData);
  shmdt(mutex);
  //Shared Memory Control Operation
  shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
  shmctl(shmid2, IPC_RMID, (struct shmid_ds *)0);
  
  //Selesai
  return 0;
}
