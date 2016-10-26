#include <stdio.h>
#include <stdlib.h>
int main() {
  char* path = realpath("././.././..",NULL); 
  puts(path);
  free(path);
  return 0;
}
