#include <stdio.h>
#include <stdlib.h> // exec
#include <unistd.h> // fork

int main(void)
{
    int x = 100;
    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork process failed\n");
        exit(1);
    }
    if (rc ==0) {
        x = 101;
        fprintf(stdout, "x in child process %d\n", x);
    } else {
        x =102;
        wait(NULL);
        fprintf(stdout, "x in parent process %d\n", x);
    }

    return 0;
}
