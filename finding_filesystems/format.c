/**
* Finding Filesystems
* CS 241 - Fall 2016
*/
#include "format.h"
#include <stdio.h>

void print_ls(char **files, int length) {
  int i;
  for (i = 0; i < length; ++i) {
    printf("%s\n", files[i]);
  }
}
