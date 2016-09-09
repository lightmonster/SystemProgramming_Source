#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
   close(1); // close standard out
   open("log.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
   puts("Captain's log");
   chdir("/usr/include");
   // fflush before exec- otherwise you won't see "captains log"
   fflush(stdout)
   execl("/bin/ls", "/bin/ls",".",(char*)NULL); // "ls ."
   perror("exec failed");
   return 0; // Not expected
}
