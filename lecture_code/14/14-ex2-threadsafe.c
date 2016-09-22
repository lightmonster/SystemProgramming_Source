#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


pthread_mutex_t m ;

size_t capacity = 64;
size_t size = 0;
char**data;

void push(char*value) {
  pthread_mutex_lock(&m);
  if(size == capacity) {
    capacity *= 2;
    data=realloc(data,capacity *sizeof(char*));
  }
  data[size++] = value;  
  pthread_mutex_unlock(&m);
}
char* pop() {
  pthread_mutex_lock(&m);
  char* result = data[--size];
  pthread_mutex_unlock(&m);
  
  return result;
}


void* runner(void*result) {
  int i;
  for(i = 0; i < 1000; i++)
    push("uiuc");

  * ((int*) result) += i; // race condition? 
  return NULL;
}

int main() {
  data = malloc (capacity * sizeof(char*));
  push(NULL); 
  pthread_t tid1, tid2, tid3;
  int itemsadded= 0;
  pthread_create(&tid1, 0, runner, &itemsadded);
  pthread_create(&tid2, 0, runner, &itemsadded);
  pthread_create(&tid3, 0, runner, &itemsadded);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  printf("%d items added. Now lets remove them\n..",itemsadded);
  int count = 0;
  while(pop()) {  count++; }
  printf("%d items removed\n", count);
}
