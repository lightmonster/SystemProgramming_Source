#include <stdio.h>
int main(int argc, char**argv) {
  int bad = (int) "Hello";
  puts( (char*) bad);
  printf("Value of Hello literal is %p\n","Hello");
  return 0;
}

