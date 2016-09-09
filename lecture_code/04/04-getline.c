#include <stdio.h>

int main(int argc, char**argv) {
  char *s = NULL;
  size_t n = 0; // unsigned
  // ssize_t // signed!
  while(1) {
    ssize_t bytesread = getline(&s, &n, stdin);
    printf("Bytes read %d\n", bytesread);
    if( bytesread < 1) break;
    printf("Buffer is at %p and size is %d\n", s, (int) n);
    printf("You said: %s", s);
  }
}
