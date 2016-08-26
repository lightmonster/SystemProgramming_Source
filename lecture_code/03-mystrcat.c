#include <stdio.h>
#include <stdlib.h>

// dest must be large enough to hold both strings
// ie strlen(dest) + strlen(src) + 1

void mystrcat(char*dest, const char* src) {

  dest += strlen(dest);
  while( *src) {
    *dest = *src;
    dest ++;
    src ++;
  }
  * dest = '\0';
}

