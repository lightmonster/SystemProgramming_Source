#include <pthread.h>
pthread_mutex_t m;
pthread_cond_t cv;
int reading = 0, writing =0;
char* array[100];

char* read(int key) {
    if(key<0 || key >99) return NULL;

    pthread_mutex_lock(&m);
    while (writing)
        pthread_cond_wait(&cv, &m);
    reading++;
    pthread_mutex_unlock(&m);
/* Read here! */
    char* result = array[key];

    pthread_mutex_lock(&m);
    reading--;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);
    return result;
}

void write(int key, char* value) {
    if(key < 0 || key > 99) return;
    pthread_mutex_lock(&m);
    while (reading || writing)
      pthread_cond_wait(&cv, &m);
    writing++;
    pthread_mutex_unlock(&m);
 /* Write here! */
    array[key] = value;
    pthread_mutex_lock(&m);
    writing--;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);
}
