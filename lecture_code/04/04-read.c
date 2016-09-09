#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
int main(int argc, char**argv) {
  void*buffer = malloc(100);
  ssize_t bytesread = read( 0 /*stdin */ , buffer, 99);
  write(1, buffer, bytesread);
  return 0;
}

