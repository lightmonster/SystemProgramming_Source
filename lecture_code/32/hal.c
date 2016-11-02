#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

struct stat s;
char* filename = "secret.txt";
void quit(char*mesg) {
  perror(mesg);
  exit(1);
}

int main() { // who am i?
  
  struct passwd *pw;
  pw = getpwuid(getuid());
  if(pw) printf("getuid: %d, Hello %s,\n", getuid(), pw->pw_name);
  
  pw = getpwuid(geteuid());
  if(pw) printf("geteuid(): %d, You are effectively %s,\n", geteuid(), pw->pw_name);

  printf("Opening file %s...\n", filename);

  FILE* f = fopen(filename,"r");
  if( !f ) quit("fopen failed");
  
  if( stat(filename, &s) !=0 ) quit("stat failed");
  size_t size = s.st_size;
  char* buffer = malloc(size);
  size_t bytesread = fread(buffer, 1, size, f);
  fclose(f);
  fwrite(buffer, 1, bytesread, stdout);
  free(buffer);
}
