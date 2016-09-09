#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {
  char* homedir = getenv("HOME");
  char*path = getenv("PATH");
  puts(path);
  puts(homedir);
  return 0;
}

