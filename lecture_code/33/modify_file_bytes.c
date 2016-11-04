#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void quit(char*mesg) {perror(mesg); exit(1);}
struct stat s;

int main() {
  int fd = open("dsl-4.4.10.iso", O_RDWR);
  if(fd <0) quit("open");

  int failed = fstat(fd, &s);
  if( failed) quit("fstat");

  char *ptr = mmap(NULL, s.st_size, 
    PROT_READ | PROT_WRITE, 
    MAP_FILE | MAP_SHARED, fd, 0);

  strcpy( ptr + 0x304f85c, "- HACKED BY ANGRAVE @ UIUC -");
  munmap(ptr,s.st_size);
  close(fd);
  return 0;
}

