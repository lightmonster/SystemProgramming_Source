/**
* Finding Filesystems
* CS 241 - Fall 2016
*/
#pragma once

#include <stdint.h>
#include <time.h>

#define KILOBYTE (1024)

#define INODES_NUMBER (1024)
#define DATA_NUMBER (2 * KILOBYTE)
#define MAX_FILENAME (248)
#define FILE_NAME_ENTRY (MAX_FILENAME + 8)
#define UNASSIGNED_NODE (-1)

#define TYPE_FILE 1
#define TYPE_DIRECTORY 2
#define TYPE_SINGLE_INDIRECT 3
#define TYPE_PIPE 4

#define NUM_DIRECT_INODES 11
#define SEGFAULT *((char *)NULL) = 1;

typedef struct {

  uint64_t size;         /* Size of the mmaped region */
  uint64_t inode_count;  /* Multiple of 64 */
  uint64_t dblock_count; /* Multiple of 64 */
  char data_map[0];

} superblock;
/*
        An inode is set if the num_hard_links is 0.

        After that block we have dblock_count bytes, byte i
                is 0 if that corresponding data block is free

        The superblock is exactly 1 kilobyte in size maximum

        You _do not_ need to worry about this implementation
        this is abstracted away from you!
*/

typedef struct {

  uint8_t owner;            /* ID of the owner */
  uint8_t group;            /* group ID */
  uint16_t permissions;     /* <d,f,c,p>rwxrwxrwx */
  uint32_t hard_link_count; /* reference count, when hit 0 */
  time_t last_access;       /* read change */
  time_t last_modification; /* metadata change only */
  time_t last_change;       /* write change */
  uint64_t size;            /* size of the file in bytes */

  int direct_nodes[NUM_DIRECT_INODES]; /* number of direct data nodes */
                                       /* the number of used nodes correlates */
                                       /* to the size and block */
  int single_indirect;                 /* points to a singly indirect block */
} inode;

typedef struct {
  char data[16 * KILOBYTE]; /* Carry on the abstraction */
} data_block;

typedef struct {
  superblock *meta;      /* Stores the information about system */
  inode *inode_root;     /* Array pointer to start of inodes */
  data_block *data_root; /* Array pointer to the start of datablocks */
} file_system;

void mkfs(char *args[]);
file_system *open_fs(const char *path);
void close_fs(file_system **fs_pointer);

void set_data_used(file_system *fs_pointer, int data_number, int used);
int get_data_used(file_system *fs_pointer, int data_numbers);
void init_inode(inode *parent, inode *init);
int first_unused_inode(file_system *fs_pointer);
int first_unused_data(file_system *fs_pointer);
inode *parent_directory(file_system *fs, char *path, char **filename);
int valid_filename(const char *filename);
int add_single_indirect_block(file_system *fs_pointer, inode *node);
int add_data_block_to_inode(file_system *fs_pointer, inode *node);

inode *get_inode(file_system *fs, char *path);
inode **get_inodes(file_system *fs, char **path);

void fs_ls(file_system *fs, char *path);
void fs_cat(file_system *fs, char *path);
void fs_chmod(file_system *fs, char *path, int new_permissions);

void fs_stat(file_system *fs, char *paths);
void fs_cp(file_system *fs, char *file, char *path);
void fs_mkdir(file_system *fs, char *path);
inode *fs_touch(file_system *fs, char *path);