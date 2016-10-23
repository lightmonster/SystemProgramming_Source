#include <stdio.h>
#include <unistd.h>
int main() {
    int fh[2];
    pipe(fh);
    int b = 0;
    #define MESG "..............................."
    while(1) {
        printf("%d\n",b);
        write(fh[1], MESG, sizeof(MESG));
        b += sizeof(MESG);
    }
    return 0;
}
