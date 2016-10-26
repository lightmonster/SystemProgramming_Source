#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char**argv) {
  if(argc != 2) return  fprintf(stderr, "Usage: %s path\n", argv[0]);
  char* basedir = realpath(".", NULL);
  char* absolute;
  asprintf(&absolute,  "%s/%s", basedir, argv[1] );
  
  printf("%s : ",absolute);
  char* request = realpath( absolute, NULL);

  if( strncmp(basedir, request, strlen(basedir) ) )
    puts("Denied!");
  else 
    puts("OK");

  free(basedir);
  free(request);
  free(absolute);
  return 0;
}
