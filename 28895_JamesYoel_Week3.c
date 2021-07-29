#include <stdio.h>
#include <string.h>

static char buffer[] = "foobar";
char filename[] = "dummy.txt";

int main (void){
  char read_str[100];
  FILE *stream, *stream1;
  int size;
  char my_str[100];
  int newname;
  char new_filename[100];
  
  //Menentukan nama file
  printf("Input new name for file: ");
  scanf("%s", new_filename);
  
  //Menentukan ukuran yang ingin diinput dan dibaca
  printf("Input file size: ");
  scanf("%d", &size);
  
  //membaca char buffer sesuai dengan size.
  stream = fmemopen(buffer, size, "r");
  //Error Handling
  if(!stream){
    perror("Failed to open string!");
    return -1;
  }
  //Append pada filename (read and write).
  stream1 = fopen (filename, "a+");
  //Error Handling
  if(!stream1){
    perror("Failed to open file!");
    return -1;
  }
  
  if (stream1 != NULL){
    //Memposisikan stream1 diawal kembali (karena append mulai di akhir)
    rewind(stream1);
    //Mengambil sebaris pada stream kepada read_str sesuai dengan size+1
    //Plus Error Handling
    if(!fgets(read_str, size+1, stream)){
      perror("Failed to read!");
      return -1;
    }
    //Menulis sebaris read_str pada stream1
    //Plus Error Handling
    if(fputs(read_str, stream1) == EOF){
      perror("Failed to write!");
      return -1;
    }
    //Memposisikan stream1 diawal kembali
    rewind(stream1);
    //Mengambil sebaris pada stream1 kepada my_str sesuai dengan ukuran my_str
    //Plus Error Handling
    if(!fgets(my_str, sizeof(my_str), stream1)){
      perror("Failed to read!");
      return -1;
    }
    //Menampilkan isi my_str
    printf("%s\n", my_str);
  }
  //Menamakan file sesuai inputan user
  newname = rename(filename, new_filename);
  //Menutup stream
  //Plus Error Handling
  if(fclose(stream)){
    perror("fclose");
    return -1;
  }
  //Menutup stream1
  //Plus Error Handling
  if(fclose(stream1)){
    perror("fclose");
    return -1;
  }
  //Selesai
  return 0;
}
