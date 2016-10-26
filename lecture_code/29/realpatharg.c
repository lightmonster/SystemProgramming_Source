#include <stdio.h>
#include <stdlib.h>
int main(int argc, char**argv) {
  if(argc != 2) return  fprintf(stderr, "Usage: %s path\n", argv[0]);

  char* path = realpath(argv[1], NULL); 
  puts(path);
  free(path);
  return 0;
}
