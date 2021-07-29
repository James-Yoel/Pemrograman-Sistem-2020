#include <stdio.h>
#include <stdlib.h>

//Menghitung waktu waiting antar proses
void waitingTime(int job[], int n, int lengthJob[], int waitTime[]){
  int i;
  //Awal wait = 0
  waitTime[0] = 0;
  for(i = 1; i < n; i++){
    //panjang proses sebelum + wait time proses sebelum
    waitTime[i] = lengthJob[i - 1] + waitTime[i - 1];
  }
  return;
}

//Menghitung waktu turn around antar proses
void turnTime(int job[], int n, int lengthJob[], int waitTime[], int turnAround[]){
  int i;
  for(i = 0; i < n; i++){
    //Panjang proses + waktu tunggu proses
    turnAround[i] = lengthJob[i] + waitTime[i];
  }
  return;
}

//Fungsi untuk menghitung waktu keseluruhan
void avgTime(int job[], int n, int lengthJob[]){
  int waitTime[n], turnAround[n], totalWait = 0, totalTurn = 0;
  int i;
  //Mendapatkan waktu wait
  waitingTime(job, n, lengthJob, waitTime);
  //Mendapatkan waktu turn around
  turnTime(job, n, lengthJob, waitTime, turnAround);
  printf("Job\t Length\t Waiting Turn Around\n");
  //Print hasil untuk setiap proses, panjang proses, waiting time, dan turn around time proses
  for(i = 0; i < n; i++){
    //Menghitung waktu total wait
    totalWait = totalWait + waitTime[i];
    //Menghitung waktu total turn around
    totalTurn = totalTurn + turnAround[i];
    printf("%d\t %d\t %d\t %d\n", job[i], lengthJob[i], waitTime[i], turnAround[i]); 
  }
  //Rata-rata waktu wait
  printf("Average Waiting Time = %f\n", (float)totalWait / (float)n);
  //Rata-rata waktu turn around
  printf("Average Turn Around Time = %f\n", (float)totalTurn / (float)n);
  printf("\n");
  return;
}

//Fungsi utama cpu scheduling
void cpuScheduling(){
  int i;
  int n;
  //Meminta user untuk jumlah proses
  printf("Number of processes: ");
  scanf("%d", &n);
  int job[n];
  //Pemasangan nomor/id proses
  for(i = 0; i < n; i++){
    job[i] = i+1;
  }
  //Meminta user untuk panjang setiap proses
  int lengthJob[n];
  for(i = 0; i < n; i++){
    printf("Length of Job %d: ", i+1);
    scanf("%d", &lengthJob[i]);
  }
  //Waktu proses dihitung
  avgTime(job, n, lengthJob);
  return;
}

//Fungsi untuk melakukan seek
void seekDisk(int disk[], int n, int headPosition){
  int i, totalSeek = 0, seek[n];
  //Perhitungan seek
  for(i = 0; i < n; i++){
    //posisi disk setelah dikurang posisi disk sekarang (absolut)
    seek[i] = abs(disk[i+1] - disk[i]);
    //Menghitung waktu total seek
    totalSeek = totalSeek + seek[i];
  }
  printf("Disk\t Next Disk\t Seek\n");
  //Print untuk setiap posisi disk, disk setelahnya, dan seek time
  for(i = 0; i < n; i++){
    printf("%d\t %d\t\t %d\n", disk[i], disk[i+1], seek[i]);
  }
  //Waktu total seek
  printf("Total Seek Time = %d\n", totalSeek);
  //Waktu rata-rata seek
  printf("Average Seek Time = %f\n", (float)totalSeek / (float)n);
  printf("\n");
  return;
}

void diskScheduling(){
  int i, n, headPosition;
  //Meminta user untuk jumlah disk
  printf("Number of disks: ");
  scanf("%d", &n);
  int disk[n+1];
  //Meminta user untuk setiap posisi disk
  for(i = 1; i < n+1; i++){
    printf("Position of Disk %d: ", i);
    scanf("%d", &disk[i]);
  }
  //Meminta user awalan posisi saat dijalankan
  printf("Initial Head Position: ");
  scanf("%d", &headPosition);
  //Assign disk pertama sebagai posisi awal
  disk[0] = headPosition;
  //Menghitung waktu seek
  seekDisk(disk, n, headPosition);
  return;
}

int main(){
  int opt = 0;
  while(opt != 3){
    printf("Scheduling\n");
    printf("1. CPU Scheduling\n");
    printf("2. Disk Scheduling\n");
    printf("3. Exit\n");
    printf("Choose Option: ");
    scanf("%d", &opt);
    if(opt != 3){
      switch(opt){
        case 1: cpuScheduling(); break;
        case 2: diskScheduling(); break;
        default: printf("Wrong Input...\n");
      }
    }
  }
  printf("Thank You !\n");
  return 0;
}
