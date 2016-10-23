#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    FILE* f = fopen("data.csv","w");
    
    fprintf(f,"123\n");
    
    fseek(f,0,SEEK_END);
    long size = ftell(f);
    printf("%d bytes\n",(int) size);
    if(fork()) {
        fseek(f,0,SEEK_SET);
        
        fclose(f);
    } else {
        sleep(1);
        fprintf(f,"BigOne at %d!\n",getpid());
        fclose(f);
    }
    return 0;
}
