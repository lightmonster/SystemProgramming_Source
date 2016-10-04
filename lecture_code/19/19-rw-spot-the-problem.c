#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t cv;
int reading = 0, writing =0;
char* array[100];

char* read_cache(int key) {
    if(key<0 || key >99) return NULL;

    pthread_mutex_lock(&m);
    while (writing)
        pthread_cond_wait(&cv, &m);
    reading++;
    pthread_mutex_unlock(&m);
/* Read here! */
    char* result = array[key];
    sleep(2);

    pthread_mutex_lock(&m);
    reading--;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);
    return result;
}

void write_cache(int key, char* value) {
    if(key < 0 || key > 99) return;
    pthread_mutex_lock(&m);
    while (reading || writing)
      pthread_cond_wait(&cv, &m);
    writing++;
    pthread_mutex_unlock(&m);
 /* Write here! */
    array[key] = value;
    sleep(3);

    pthread_mutex_lock(&m);
    writing--;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);
}
