#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void hey(int signal) {
    write(1,"Hey\n",4);
}

int main() {
    int filedes[2];
    signal(SIGPIPE,hey);
    
    pipe( filedes );
    sleep(1);
    pid_t child = fork();
    if(child > 0) { 
        /* I must be the parent */
        char buffer[80];
        int bytesread = read(filedes[0] , buffer, sizeof(buffer));
        write(1, buffer, bytesread);
        printf("\n%d bytes read\n", bytesread);
        // do something with the bytes read
    } else {
        //fdopen(int fd, const char *mode);
        FILE* f = fdopen(filedes[1],"w");
        fprintf(f,"Hi!\n");
        fflush(f);
    }
    sleep(1);
    return 0;
}
