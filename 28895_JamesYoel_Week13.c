#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct{
  int id;
  int arr;
  int cpu;
  int io;
} task;

void waitingTime(task runTask[], int n, int wait[]){
  int remain[n], i, complete = 0, t = 0, minM = INT_MAX, shortest = 0, finish;
  bool check = false;
  //Menetapkan waktu tersisa untuk setiap cpuTime
  for(i = 0; i < n; i++){
    remain[i] = runTask[i].cpu;
  }
  //Selama semua task belum dijalankan
  while(complete != n){
    //Mencari task dengan waktu tersisa paling rendah dari seluruh task yang telah tiba pada waktu t
    for(i = 0; i < n; i++){
      if((runTask[i].arr <= t) && (remain[i] < minM) && (remain[i] > 0)){
        minM = remain[i];
        shortest = i;
        check = true;
      }
    }
    if(check == false){
      t++;
    }
    //Mengurangi waktu task tersisa yang dijalankan dengan satu
    remain[shortest]--;
    //Update nilai minimum
    minM = remain[shortest];
    if(minM == 0){
      minM = INT_MAX;
    }
    //Jika task yang sedang dijalankan sudah selesai
    if(remain[shortest] == 0){
      //Jumlah task yang dijalankan increment
      complete++;
      check = false;
      //Mencari waktu selesainya task tersebut
      finish = t;
      //Menghitung waiting time untuk task tersebut
      wait[shortest] = finish - runTask[shortest].cpu - runTask[shortest].arr;
      if(wait[shortest] < 0){
        wait[shortest] = 0;
      }
    }
    //Increment waktu
    t++;
  }
}

void turnAroundTime(task runTask[], int n, int wait[], int turnAround[]){
  int i;
  //Menghitung turn around time untuk seluruh task
  for(i = 0; i < n; i++){
    turnAround[i] = runTask[i].cpu + wait[i];
  }
}

void avgTime(task runTask[], int n){
  int wait[n], turnAround[n], totalWait = 0, totalAround = 0, i;
  //Mencari Waiting Time
  waitingTime(runTask, n, wait);
  //Mencari Turn Around Time
  turnAroundTime(runTask, n, wait, turnAround);
  printf("Task\tWait\tResponse\tTurn Around\n");
  for(i = 0; i < n; i++){
    //Menghitung total waiting time dan turn around time
    totalWait = totalWait + wait[i];
    totalAround = totalAround + turnAround[i];
    printf("%d\t%d\t%d\t\t%d\n", runTask[i].id, wait[i], runTask[i].cpu, turnAround[i]);
  }
  printf("Total Waiting Time = %d\n", totalWait);
  //Menampilkan dan menghitung avg waiting time
  printf("Avg Waiting Time = %f\n", (float)totalWait / (float)n);
  printf("Total Turn Around Time = %d\n", totalAround);
  //Menampilkan dan menghitung avg turn around time
  printf("Avg Turn Around Time = %f\n", (float)totalAround / (float)n);
}

int main(){
  int n, i;
  //Meminta Jumlah Task
  printf("Masukkan jumlah task : ");
  scanf("%d", &n);
  printf("\n");
  task runTask[n];
  //Meminta data untuk setiap task sesuai dengan struct
  for(i = 0; i < n; i++){
    runTask[i].id = i+1;
    printf("Task ID %d\n", i+1); 
    printf("Waktu ketibaan task : ");
    scanf("%d", &runTask[i].arr);
    printf("Lama Waktu Menggunakaan Resource CPU : ");
    scanf("%d", &runTask[i].cpu);
    printf("Lama Waktu Meggunakaan Resource I/O : ");
    scanf("%d", &runTask[i].io);
    printf("\n");
  }
  //Mencari waktu
  avgTime(runTask, n);
  return 0;
}
