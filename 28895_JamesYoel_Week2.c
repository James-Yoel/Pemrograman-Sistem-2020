//Menambahkan library
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  //membuat variabel
  char my_write_str[] = "1234567890";
  char my_read_str[100];
  char my_filename[] = "dummy.txt";
  int my_file_descriptor, close_err;
  char new_filename[100];
  int newname;
  int size;
  
  //Program meminta user memasukkan ukuran teks yang akan ditulis dan dibaca
  printf("Input file size: ");
  scanf("%d", &size);
  
  //Program membuka dummy.txt dengan flags O_RDWR untuk read dan write, 
  //O_CREAT untuk membuat file tersebut jika belum ada, dan O_TRUNC yang akan mengtruncate file tersebut menjadi zero length 
  my_file_descriptor = open (my_filename, O_RDWR | O_CREAT | O_TRUNC);
  
  //Program menulis ulang file tersebut dengan my_write_str dan ukuran yang diinput oleh user
  write (my_file_descriptor, (void *) my_write_str, size);

  //Memastikan data yang telah ditulis langsung tersimpan pada disk
  fsync (my_file_descriptor);
  
  //Program menentukan posisi 0 pada my_file_descriptor sebagai pos
  lseek (my_file_descriptor, 0, SEEK_SET);
  
  //Program membaca isi my_file_descriptor yang disimpan pada my_read_str sesuai dengan size yang telah ditetapkan oleh user
  read (my_file_descriptor, (void *) my_read_str, size);
  
  //Program menentukan my_read_str dengan array size sebagai akhiran.
  my_read_str[size] = '\0';
  
  //Program meminta user menginput nama file baru
  printf("Input new name for file: ");
  scanf("%s", new_filename);
  newname = rename(my_filename, new_filename);
  
  //Program menampilkan isi my_read_str
  printf ("String read = %s.\n", my_read_str);
  
  //Memastikan file berada pada disk sebelum ditutup
  close(my_file_descriptor);  
  
  //Program selesai
  return 0;
}
