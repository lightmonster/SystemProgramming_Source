#include <stdio.h>
#include <stdlib.h>

#define quit(mesg) {puts(mesg); exit(1);}

int main(int argc, char**argv) {
 size_t capacity = 256;
 size_t count =  0;
 int* data = malloc( capacity );
 if(!data) quit("Out of memory");

 while( !feof(stdin) && !ferror(stdin)) {
   if( count == capacity) {
       capacity *= 2;
   }
   if( fscanf(stdin, "%d", data+count) != 1) break;
   count++;
 }
 printf("%zu values read\n",count);
 data = realloc(data, capacity);

 return 0;
}
