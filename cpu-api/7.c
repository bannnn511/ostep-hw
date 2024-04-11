#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/_types/_pid_t.h>
#include "util.c"

int main() {
    const pid_t pid = fork();
    if (pid < 0) {
        errExit("failed to fork");
    }

    if (pid == 0) {
        close(STDOUT_FILENO);
        printf("children says hello\n"); // child wont print to terminal.
    } else {
        wait(NULL);
        printf("parrent says hello\n");
    }

    return 0;
}
