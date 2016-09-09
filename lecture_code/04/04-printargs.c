#include <stdio.h>

int main(int argc, char**argv) {
  printf("My process name is %s\n", argv[0]);

  int i;
  for(i =1; argv[i]; i++) 
    printf("%d : %p : %s\n", i, argv[i], argv[i] );
  return 0;
}
  

