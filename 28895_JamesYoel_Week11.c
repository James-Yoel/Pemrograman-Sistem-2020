//Define untuk fungsi strptime
#define _USE_XOPEN
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

//Fungsi menampilkan system time
void showSysTime(){
  //Mengambil current system time
  time_t sysCurrent = time(NULL);
  //Print system time
  printf("System Time: %s\n", ctime(&sysCurrent));
  return;
}

void changeSysDate(){
  struct tm sysDate;
  struct timeval newDate;
  time_t secondEpoch;
  char inputDate[25];
  char temp;
  printf("Follow the format (Jan 1 00:00:00 1900)\n");
  printf("Input the date: ");
  //Clear buffer
  scanf("%c", &temp);
  scanf("%[^\n]", inputDate);
  //Input diubah menjadi tanggal
  if(strptime(inputDate, "%b %d %H:%M:%S %Y", &sysDate) != NULL){
    //Membiarkan mktime yang menentukan sendiri
    sysDate.tm_isdst = -1;
    //mengubah tanggal menjadi detik
    secondEpoch = mktime(&sysDate);
    //set detik
    newDate.tv_sec = secondEpoch;
    //Mengubah tanggal system
    if(settimeofday(&newDate, NULL) == 0){
      printf("System Date changed !\n");
      time_t sysCurrent = time(NULL);
      printf("System Date: %s\n", ctime(&sysCurrent));
      return;
    }
    //Jika gagal mengubah
    else{
      perror("settimeofday");
      exit(EXIT_FAILURE);
    } 
  }
  //Jika gagal format penulisan tanggal
  else{
    printf("Wrong Input...\n");
    return;
  }
}

void showCpuTime(struct timespec tpstart){
  struct timespec tpend;
  long timedif;
  //Mendapatkan CPU end time
  if(clock_gettime(CLOCK_REALTIME, &tpend) == -1){
    //Error Handling
    perror("Failed to get ending time!\n");
    exit(EXIT_FAILURE);
  }
  //Perbedaan waktu (tidak menggunakan nanosecond);
  timedif = (tpend.tv_sec - tpstart.tv_sec);
  printf("CPU Start Time: %ld seconds\n", tpstart.tv_sec);
  printf("CPU End Time: %ld seconds\n", tpend.tv_sec);
  printf("Total CPU time: %ld seconds\n", timedif);
  return;
}

int main(){
  int opt = 0;
  struct timespec tpstart;
  
  //Mendapatkan CPU start time
  if(clock_gettime(CLOCK_REALTIME, &tpstart) == -1){
    //Error Handling
    perror("Failed to get starting time!\n");
    exit(EXIT_FAILURE);
  }
  
  while(opt != 4){
    printf("Time Manager\n");
    printf("1. Show current system time\n");
    printf("2. Change system date\n");
    printf("3. Show CPU Time\n");
    printf("4. Exit\n");
    printf("Choose Option: ");
    scanf("%d", &opt);
    if(opt != 4){
      switch(opt){
        case 1: showSysTime(); break;
        case 2: changeSysDate(); break;
        case 3: showCpuTime(tpstart); break;
        default: printf("Wrong Input...\n");
      }
    }
  }
  printf("Thank You !\n");
  return 0;
}
