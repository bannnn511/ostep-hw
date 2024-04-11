#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.c"

int main() {
    int pfd[2];

    if (pipe(pfd) == -1) {
        errExit("failed pipe");
    }

    pid_t pid[2];
    pid[0] = fork();
    if (pid[0] == -1) {
        errExit("failed fork");
    }

    if (pid[0] == 0) {
        // read end is unused
        if (close(pfd[0]) == -1) {
            errExit("child close fd0");
        }

        if (pfd[1] != STDOUT_FILENO) {
            if (dup2(pfd[1], STDOUT_FILENO) == -1) {
                errExit("dup2 1");
            }
            if (close(pfd[1]) == -1) {
                errExit("close 1");
            }
        }

        printf("first child says hello\n");
    } else {
        pid[1] = fork();
        if (pid[1] == -1) {
            errExit("failed fork");
        }
        if (pid[1] == 0) {
            // write end is unused
            if (close(pfd[1]) == -1) {
                errExit("child 2 close fd1");
            }

            if (pfd[0] != STDIN_FILENO) {
                if (dup2(pfd[0], STDIN_FILENO) == -1) {
                    errExit("dup2 0");
                }
                if (close(pfd[0]) == -1) {
                    errExit("close 0");
                }
            }

            char buf[BUFSIZ];
            read(STDIN_FILENO, buf, BUFSIZ);
            printf("Second child print: %s\n", buf);
        } else {
            // parent
            if (waitpid(pid[0], NULL, 0) == -1)
                errExit("waitpid");
            if (waitpid(pid[1], NULL, 0) == -1)
                errExit("waitpid");

            if (close(pfd[0]) == -1) {
                errExit("parent close fd0");
            }

            if (close(pfd[1]) == -1) {
                errExit("parent close fd1");
            }

            printf("parent says goodbye\n");
        }
    }

    return 0;
}
