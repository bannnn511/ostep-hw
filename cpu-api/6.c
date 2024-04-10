#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/_types/_pid_t.h>
#include "util.c"

/*
 * waitpid can wait for a specific child
 * nonblocking wait
 * get children status
 */
int main() {
    int status;
    pid_t pid = fork();
    if (pid < 0) {
        errExit("fork failed");
    }

    if (pid == 0) {
        const pid_t wait_return = waitpid(-1, NULL, WUNTRACED | WCONTINUED);
        printf("child wait return: %d\n", wait_return);
    } else {
        const pid_t wait_return = waitpid(-1, &status, WUNTRACED | WCONTINUED);

        if (wait_return == -1) {
            errExit("waitpid");
        }

        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            printf("parent wait return: %d\n", wait_return);
            printf("child terminated normally");
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
