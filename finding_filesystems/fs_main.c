/**
* Finding Filesystems
* CS 241 - Fall 2016
*/
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

void print_general_help() {
  printf("Help: File System Navigator\n\n");
  printf("./minixfs mkfs <filename>\n");

  printf("./minixfs <file_system> ls [path]\n");
  printf("./minixfs <file_system> cat  <path>\n");
  printf("./minixfs <file_system> chmod  <path> <permissions>\n\n\n");

  printf("./minixfs <file_system> stat <path>\n");
  printf("./minixfs <file_system> cp <file> <fs_path>\n");
  printf("./minixfs <file_system> touch <path>\n");
  printf("./minixfs <file_system> mkdir <path>\n");
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    print_general_help();
    return 1;
  }
  argv++;
  if (!strcmp(*argv, "mkfs")) {
    mkfs(++argv);
    return 0;
  }

  file_system *fs = open_fs(argv[0]);
  if (!fs) {
    fprintf(stderr, "Filesystem not found: %s\n", argv[0]);
    return 1;
  }
  argv++;
  if (!strcmp(*argv, "ls")) {
    fs_ls(fs, *++argv);
  } else if (!strcmp(*argv, "cat")) {
    fs_cat(fs, *++argv);
  } else if (!strcmp(*argv, "chmod")) {
    if (argc != 5) {
      printf("Invalid chmod command\n");
      return 1;
    }
    char *path = *++argv;
    char *permissions = *++argv;
    int new_permissions = (int)strtol(permissions, NULL, 8);
    fs_chmod(fs, path, new_permissions);
  } else if (!strcmp(*argv, "stat")) {
    fs_stat(fs, *++argv);
  } else if (!strcmp(*argv, "touch")) {
    fs_touch(fs, *++argv);
  } else if (!strcmp(*argv, "mkdir")) {
    fs_mkdir(fs, *++argv);
  } else if (!strcmp(*argv, "cp")) {
    char *old = *++argv;
    char *new = *++argv;
    fs_cp(fs, old, new);
  } else {
    printf("Invalid command");
    print_general_help();
  }
  close_fs(&fs);

  return 0;
}
