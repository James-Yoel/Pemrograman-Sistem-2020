#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* increment(){
  int *x;
  //Menggunakan calloc karena array dan agar di assign 0
  //*2 untuk x[0] dan x[1]
  x = (int *) calloc(2, sizeof(int)*2);
  //error handler
  if(!x){
    perror("calloc");
    exit(EXIT_FAILURE);
  }
  int i;
  for(i=0;i<10;i++){
    x[0] += 1;
    x[1] += 2;
  }
  return x;
}

char *tukar(){
  char *a, *b, *c;
  a = (char*) malloc(sizeof(char) * 50);
  //Error Handler
  if(!a){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  b = (char*) malloc(sizeof(char) * 50);
  //Error Handler
  if(!b){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  c = (char*) malloc(sizeof(char) * 50);
  //Error Handler
  if(!c){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  strcpy(a, "string a");
  strcpy(b, "string b");
  
  printf("\nBefore: \n");
  printf("a = %s\n", a);
  printf("b = %s\n", b);
  //Free terlebih dahulu agar tidak terjadi memory leak (c sudah tidak dipakai)
  free(c);
  //Penukaran nilai
  c = b;
  b = a;
  a = c;
  
  printf("\nAfter : \n");
  printf("a = %s\n", a);
  printf("b = %s\n", b); 
  
  //Free karena tidak dipakai
  free(b);
  
  return c;
}

int main(){
  int *x;
  char *y;
  x = increment();
  printf("x0 = %d\n", x[0]);
  printf("x1 = %d\n", x[1]);
  //free karena sudah tidak dipakai
  free(x);
  y = tukar();
  printf("%s\n", y);
  //free karena sudah tidak dipakai
  free(y);
  //Menunggu input
  getchar();
  return 0;
}
