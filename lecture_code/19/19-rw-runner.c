#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CLEARSCREEN "\033[2J\033[H"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"
// gcc 19-*.c -pthread
// Illustrate write starvation by constantly adding new readers.

int reader_count, writer_count;
extern int reading, writing;

void write_cache(int key, char* value);
char* read_cache(int key);

pthread_mutex_t add_mutex = PTHREAD_MUTEX_INITIALIZER;

void add(int *ptr, int value) {
  pthread_mutex_lock( &add_mutex);
  *ptr += value;
  pthread_mutex_unlock( &add_mutex);
}

void* reader(void*arg) {
    puts("New reader");
    add(&reader_count,1);
    char* mesg = read_cache(10);
    add(&reader_count,-1);
    puts("Reader done");
    return NULL;
}

void* writer(void*arg){
   puts("New writer");
   add(&writer_count,1);
   write_cache(10, "hello");
   add(&writer_count,-1);
   puts("Writer done");

   return NULL;
}

void* display(void*arg) {
  while(1) {
    printf( CLEARSCREEN );
    pthread_mutex_lock( &add_mutex);
    int reader_waiting = reader_count - reading;
    int writer_waiting = writer_count - writing;
    char* reader_waiting_color = reader_waiting ? RED : WHITE;
    char* reader_reading_color = reading ? GREEN : WHITE;
    char* writer_waiting_color = writer_waiting ? RED : WHITE;
    char* writer_writing_color = writing ? GREEN : WHITE; 
    printf("%d readers | %s%d waiting" WHITE " | %s%d active" WHITE "\n", reader_count, reader_waiting_color,reader_waiting, reader_reading_color,reading);
    printf("%d writers | %s%d waiting" WHITE " | %s%d active" WHITE "\n", writer_count, writer_waiting_color,writer_waiting,writer_writing_color, writing);
    pthread_mutex_unlock( &add_mutex);
    puts("Type " RED "r" WHITE " or " RED "w" WHITE " and press " GREEN "return" WHITE " to create new reader or writer. Read operations require 2 seconds, Write operations require 3 seconds.");
    usleep(5E5);
  }
  return NULL;
}

  
int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, display,NULL);
  while(1) {
    int c = getchar();
    if(c== 'r') pthread_create(&tid, NULL, reader, NULL);
    else if(c=='w') pthread_create(&tid, NULL, writer, NULL);
    else if (c=='q') break;
  } 
  return 0;
}
