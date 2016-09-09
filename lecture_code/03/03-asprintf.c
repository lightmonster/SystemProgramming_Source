#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
// int asprintf(char **strp, const char *fmt, ...)

int main(int argc, char**argv) {

  char * ptr;
  asprintf( & ptr, "Meaning of life:..... %d \n", 6*7);

  for(int i =0; ptr[i] ; i++) {
    putchar( ptr[i]);  fflush(stdout);
    usleep(1E5); // 1/10th second
  }
  free(ptr);
  return 0;
}

