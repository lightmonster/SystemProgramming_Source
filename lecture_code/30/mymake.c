#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
//Compile with 
// gcc mymake-solution.c -o mymake

int main() {
  struct stat src, tgt;
  int src_ok = stat("prog.c", &src);

  if(src_ok) {perror("No source?"); return 1;}

  int tgt_ok = stat("a.out", &tgt);

  double delta = difftime(

  if() {
    char* reason = tgt_ok ? "Missing binary":"Out of date";
    printf("Compiling... (%s)\n" , reason);

    system("gcc prog.c");
  }
  else puts("nothing to do");

  return 0;
}
