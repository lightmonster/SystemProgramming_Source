#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct stat s;

void quit(char*mesg) {perror(mesg); exit(1);}

int main() {
  int fd = open("dsl-4.4.10.iso", O_RDONLY);
  if(fd <0) quit("open");

  int failed = fstat(fd, &s);
  if( failed) quit("fstat");

  char *ptr = mmap(NULL, s.st_size, 
    PROT_READ , 
    MAP_FILE | MAP_SHARED, fd, 0);

  for(off_t i=0; i< s.st_size;i++) {
     if((i%64) ==0) printf("\n%zx ",i);
     putchar(ptr[i] >31 ? ptr[i] : '.');
  }
  printf("\n %zx bytes printed.\n", s.st_size);
  return 0;
}

