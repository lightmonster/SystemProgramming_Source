#include <stdio.h>

int main(int argc, char**argv) {
  int num= -99;
  char c='#';
  int result = scanf("%d %c", &num, &c);

  printf("Values: %d %c\n", num, c);
  printf("Return value: %d\n", result);
  return 0;
}
