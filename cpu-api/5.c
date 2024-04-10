#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/_types/_pid_t.h>
#include "util.c"

int main(int argc, char *argv[]) {
    const pid_t pid = fork();
    if (pid < 0) {
        errExit("fork failed");
    }

    if (pid == 0) {
        const pid_t wait_return = wait(NULL);
        printf("child wait return: %d\n", wait_return);
    } else {
        const pid_t wait_return = wait(NULL);
        printf("parent wait return: %d\n", wait_return);
    }

    return 0;
}
