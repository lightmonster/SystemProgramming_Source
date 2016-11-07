#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
void quit(char*mesg) { perror(mesg); exit(1); }

int main(int argc, char**argv) {
    sigset_t mask;
    sigset_t orig_mask;
    sigemptyset (&mask);
    sigaddset (&mask, SIGTERM);
    sigaddset (&mask, SIGINT);
 
    if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) quit("sigprocmask");
    puts("Raising SIGTERM");

    raise( SIGTERM);
    sleep(3);
    puts("Resetting mask...");
    sigprocmask(SIG_SETMASK, &orig_mask, NULL);
    puts("sleeping...");
    sleep(10);
    puts("exiting normally");
    return 1;
}
