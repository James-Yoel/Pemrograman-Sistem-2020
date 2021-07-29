#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

int main(){
  int fd;
  int len;
  //descriptor untuk FIFO;
  char buf[PIPE_BUF];
  if((fd=open("fifo1", O_RDONLY)) < 0){
    perror("open");
    exit(EXIT_FAILURE);
  }
  while((len = read(fd, buf, PIPE_BUF-1)) > 0)
    printf("Read: %s", buf);
  close(fd);
  exit(EXIT_SUCCESS);
}
