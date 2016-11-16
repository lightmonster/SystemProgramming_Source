#ifndef DEPLOY
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#endif
#include "utils.h"
#include "tree.h"


/*
  Look up a few nodes in the tree and print the info they contain.
  This version uses mmap to access the data.

  ./lookup2 <data_file> <word> [<word> ...]
*/

#ifndef DEPLOY
void printHelp();
BinaryTreeNode *lookupWord(const char *data, const char *word);
BinaryTreeNode *readNode(const char *data, uint32_t offset);
int isCorrectFileFormat(const char *data);
#endif



int main(int argc, char **argv) {
  #ifndef DEPLOY
  if (argc < 3) printHelp();

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    openFail(argv[1]);
    return 2;
  }

  struct stat filestats;
  fstat(fd, &filestats);

  const char *data = mmap(NULL, filestats.st_size, PROT_READ, MAP_PRIVATE,
                          fd, 0);
  if (!data) {
    mmapFail(argv[1]);
    return 1;
  }
  close(fd);

  if (!isCorrectFileFormat(data)) {
    formatFail(argv[1]);
    return 2;
  }


  int argno;
  for (argno = 2; argno < argc; argno++) {
    const char *word = argv[argno];

    BinaryTreeNode *node = lookupWord(data, word);

    if (node) {
      assert(0 == strcmp(word, node->word));
      printFound(word, node->count, node->price);
    } else {
      printNotFound(word);
    }
  }

  munmap((void*)data, filestats.st_size);

  #endif
  return 0;
}

#ifndef DEPLOY
void printHelp() {
  printf("\n  lookup2 <data_file> <word> [<word> ...]\n\n");
  exit(1);
}


int isCorrectFileFormat(const char *data) {
  return !strncmp(data, BINTREE_HEADER_STRING, BINTREE_ROOT_NODE_OFFSET);
}


/*
  Traverse the binary tree in the file, searching for the requested word.
*/
BinaryTreeNode *lookupWord(const char *data, const char *word) {
  uint32_t offset = BINTREE_ROOT_NODE_OFFSET;
  BinaryTreeNode *node;

  node = readNode(data, offset);

  // all valid words will have at least one character

  // check if the file is empty
  if (node->word[0]) {

    while (1) {
      int compare = strcmp(word, node->word);

      if (compare == 0) {
        return node;
      } else if (compare < 0) {
        offset = node->left_child;
      } else {
        offset = node->right_child;
      }

      if (!offset) break;

      node = readNode(data, offset);
    }

  }

  return NULL;
}


/*
  Since the data is mmap'd, just return a pointer to the
  node requested. The node returned does not need to be deallocated.
*/
BinaryTreeNode *readNode(const char *data, uint32_t offset) {
  return (BinaryTreeNode*) (data + offset);
}
#endif

