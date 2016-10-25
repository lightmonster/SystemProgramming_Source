/**
* Finding Filesystems
* CS 241 - Fall 2016
*/
#include "fs.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*
        Makes a filesystem named args[0]
*/
void mkfs(char *args[]) {
  size_t size = sizeof(superblock) + DATA_NUMBER;
  size += sizeof(inode) * INODES_NUMBER + sizeof(data_block) * DATA_NUMBER;
  FILE *pf = fopen(*args, "w");
  if (!pf) {
    printf("Error, File could not be opened\n");
    exit(1);
  }
  fseek(pf, size, SEEK_SET);
  fputc('\0', pf); /* File is gaurenteed to be zeros at this point */
  fclose(pf);

  file_system *my_fs = open_fs(*args);
  inode *root = my_fs->inode_root;

  // Initialize Metadata
  my_fs->meta->size = size;
  my_fs->meta->inode_count = INODES_NUMBER;
  my_fs->meta->dblock_count = DATA_NUMBER;

  // Set up root directory as 0
  // 0 is root
  root->owner = 0;
  root->group = 0;
  root->permissions = 0755 | (TYPE_DIRECTORY << 9);
  root->single_indirect = UNASSIGNED_NODE;
  root->hard_link_count = 1;
  int i;
  for (i = 0; i < NUM_DIRECT_INODES; ++i)
    root->direct_nodes[i] = UNASSIGNED_NODE;
  time(&root->last_access);
  time(&root->last_modification);
  time(&root->last_change);
  // Initialize it to one data block size as of right now
  root->size = 0;

  close_fs(&my_fs);
}
/*
        Stats a file given a path
*/
void fs_stat(file_system *fs, char *path) {
  inode *node = get_inode(fs, path);
  if (!node)
    return;
  //*(char*)(NULL) = 1;
  printf("  File: '%s'\t", path);
  int type = node->permissions >> 9;
  if (type == TYPE_DIRECTORY) {
    printf("Type: Directory\n");
  } else {
    printf("Type: Regular File\n");
  }

  printf("Blocks: %zu\t",
         (node->size + sizeof(data_block) - 1) / sizeof(data_block));
  printf("Links: %d\t", node->hard_link_count);
  printf("Size: %zu\n", node->size);

  printf("Access: %o\t", node->permissions & 0777);
  printf("Uid: %d\t\t", node->owner);
  printf("Gid: %d\n", node->group);

  char buffer[100];
  strftime(buffer, 100, "%F %T %z", localtime(&node->last_access));
  printf("Access: %s\n", buffer);
  strftime(buffer, 100, "%F %T %z", localtime(&node->last_modification));
  printf("Modify: %s\n", buffer);
  strftime(buffer, 100, "%F %T %z", localtime(&node->last_change));
  printf("Change: %s\n", buffer);
}

void fs_cp(file_system *fs, char *file, char *path) {
  struct stat file_stat;
  if (stat(file, &file_stat) != 0) {
    fprintf(stderr, "Failed to stat file: %s\n", path);
    exit(1);
  }

  int64_t size = file_stat.st_size;
  if (size > (int64_t)sizeof(data_block) * (NUM_DIRECT_INODES * 2)) {
    fprintf(stderr, "Error file too big to copy %s\n", path);
    exit(1);
  }

  inode *nody = fs_touch(fs, path);
  nody->size = size;
  // Malloc does better than the stack for these allocations
  data_block *local = malloc(sizeof(data_block));
  int fd = open(file, O_RDONLY);
  int count = 0;
  size_t bytes;
  while ((bytes = read(fd, local, sizeof(data_block))) > 0) {
    if (count == NUM_DIRECT_INODES) {
      int node = add_single_indirect_block(fs, nody);
      nody = fs->inode_root + node;
      count = 0;
    }
    add_data_block_to_inode(fs, nody);
    memcpy(fs->data_root + nody->direct_nodes[count], local, bytes);
    count++;
  }

  free(local);
}

inode *fs_touch(file_system *fs, char *path) {
  if (*path != '/') {
    fprintf(stderr, "Path not absolute");
    return NULL;
  }
  if (get_inode(fs, path) != NULL) {
    fprintf(stderr, "Filename not unique");
    return NULL;
  }
  char *filename;
  inode *nody = parent_directory(fs, path, &filename);
  size_t name_length = strlen(filename);
  int data_last = (nody->size) / sizeof(data_block);
  if (!valid_filename(filename) || name_length > MAX_FILENAME) {
    fprintf(stderr, "Invalid Filename");
    return NULL;
  }
  if (nody->permissions >> 9 != TYPE_DIRECTORY) {
    fprintf(stderr, "Parent Not Directory");
    return NULL;
  }
  if (data_last > NUM_DIRECT_INODES) {
    if (nody->single_indirect == UNASSIGNED_NODE)
      add_single_indirect_block(fs, nody);
    nody = fs->inode_root + nody->single_indirect;
    data_last -= NUM_DIRECT_INODES;
  }

  int new_inode = first_unused_inode(fs);
  init_inode(nody, fs->inode_root + new_inode);

  size_t last_offset = nody->size % sizeof(data_block);
  data_block *blocky = fs->data_root + nody->direct_nodes[data_last];
  if (last_offset == 0) { // We are at the end of a block
    int data_block = add_data_block_to_inode(fs, nody);
    blocky = fs->data_root + data_block;
  }
  char *cpy = calloc(1, MAX_FILENAME);
  strncpy(cpy, filename, MAX_FILENAME);
  memcpy(((char *)blocky) + last_offset, cpy, MAX_FILENAME);
  sprintf(((char *)blocky) + last_offset + MAX_FILENAME, "%08x", new_inode);
  nody->size += MAX_FILENAME + 8; // 256 Bytes
  return fs->inode_root + new_inode;
}

void fs_mkdir(file_system *fs, char *path) {

  inode *node = fs_touch(fs, path);

  if (!node) {
    return;
  }
  int oldbits = node->permissions & 0777;
  node->permissions = ((TYPE_DIRECTORY) << 9);
  node->permissions |= oldbits;
}