#include<stdio.h>
#include<sys/types.h>
#include<sys/uio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
  int fs, fd;
  ssize_t bytes_read, bytes_written;
  int iovcnt;
  struct iovec iov[3];
  int i, size;
  struct stat st;
  
  //Membaca apakah jumlah input yang diterima sebanyak 3 atau tidak.
  if(argc != 3){
    perror("Error!\n");
    return 1;
  }
  //Membuka file argv[1] untuk dibaca.
  fs = open(argv[1], O_RDONLY);
  if(fs == -1){
    perror("Open fs\n");
    return 1;
  }
  //Membuka file argv[2] untuk ditulis.
  fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
  if(fd == -1){
    perror("Open fd\n");
    return 1;
  }
  //Mendapatkan byte size dari file yang ingin dibaca dan menetapkannya untuk ukuran buf.
  stat(argv[1], &st);
  size = st.st_size;
  size = size/3;
  char buf[3][size];
  //Mempersiapkan iov sesuai dengan buf
  for(i = 0; i<3; i++){
    iov[i].iov_base = buf[i];
    iov[i].iov_len = sizeof(buf[i]);
  }
  iovcnt=sizeof(iov)/sizeof(struct iovec);
  
  //Membaca isi fs dan memasukkannya kedalam iov
  if((bytes_read = readv(fs, iov, iovcnt)) != -1){
    //Menulis isi iov kedalam fd
    if((bytes_written = writev(fd, iov, iovcnt)) == EOF){
      printf("Write Error!\n");
    }
  }  
  //Menutup fs
  if(close(fs)){
    perror("Close fs\n");
    return 1;
  }
  //Menutup fd
  if(close(fd)){
    perror("Close fd\n");
  }
  //Selesai
  return 0;
}
