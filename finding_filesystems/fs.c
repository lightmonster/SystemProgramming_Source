/**
* Finding Filesystems
* CS 241 - Fall 2016
*/
#include "format.h"
#include "fs.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void fs_ls(file_system *fs, char *path) {
  // Do your magic
}

void fs_cat(file_system *fs, char *path) {
  // Your magic goes here
}

void fs_chmod(file_system *fs, char *path, int new_permissions) {
  // Your bitshifting magic goes here
}
