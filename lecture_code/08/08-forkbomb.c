#include <stdio.h>
#include <unistd.h>

// ulimit -a to list limits
// then -p or -u depending on system

int main() {
    while(1) {
        printf("Hello world. I'm process %d!\n",(int) getpid());

        if( fork() == -1) perror("Failed to fork!");

        sleep(1);
    }
    return 0;
}
