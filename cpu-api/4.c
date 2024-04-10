#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)                                                           \
do {                                                                         \
perror(msg);                                                               \
exit(EXIT_FAILURE);                                                        \
} while (0)

static void cmd_execve() {
    char *argv[10];
    argv[0] = "/bin/ls";

    char *argVec[10];
    argVec[0] = "ls";
    argVec[1] = "-l";
    argVec[2] = "-a";
    argVec[3] = NULL;
    char *envVec[] = {"Test=an"};

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("execl\n");
        if (execve(argv[0], argVec, envVec) == -1) {
            errExit("execve");
        }
    }

    if (wait(NULL) == -1) {
        errExit("wait");
    }
}

static void cmd_execle() {
    char *envVec[] = {"Test=an",NULL};

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("execle\n");
        if (execle("/bin/ls", "ls", "-l", "-a", (char *) NULL, envVec) == -1) {
            errExit("execle");
        }
    }

    if (wait(NULL) == -1) {
        errExit("wait");
    }
}

static void cmd_execlp() {
    char *envVec[] = {"Test=an",NULL};

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("execlp\n");
        if (execlp("ls", "ls", "-l", "-a", (char *) NULL, envVec) == -1) {
            errExit("execlp");
        }
    }

    if (wait(NULL) == -1) {
        errExit("wait");
    }
}

static void cmd_execvp() {
    char *argVec[10];
    argVec[0] = "ls";
    argVec[1] = "-l";
    argVec[2] = "-a";
    argVec[3] = NULL;

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("execvp\n");
        if (execvp("ls", argVec) == -1) {
            errExit("execvp");
        }
    }

    if (wait(NULL) == -1) {
        errExit("wait");
    }
}

static void cmd_execv() {
    char *argVec[10];
    argVec[0] = "ls";
    argVec[1] = "-l";
    argVec[2] = "-a";
    argVec[3] = NULL;

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("execv\n");
        if (execv("/bin/ls", argVec) == -1) {
            errExit("execv");
        }
    }

    if (wait(NULL) == -1) {
        errExit("wait");
    }
}

static void cmd_execl() {
    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("execl\n");
        if (execl("/bin/ls", "ls", "-l", "-a", (char *) NULL) == -1) {
            errExit("execl");
        }
    }

    if (wait(NULL) == -1) {
        errExit("wait");
    }
}


_Noreturn static void usage(char *name) {
    fprintf(stderr, "Usage: %s [-s|--signal] [-p|--pipe]\n", name);
    exit(EXIT_FAILURE);
}

int main(const int agrc, char *argv[]) {
    int opt;
    const struct option options[] = {
        {"execve", no_argument, NULL, '1'},
        {"execle", no_argument, NULL, '2'},
        {"execlp", no_argument, NULL, '3'},
        {"execvp", no_argument, NULL, '4'},
        {"execv", no_argument, NULL, '5'},
        {"execl", no_argument, NULL, '6'}
    };

    if ((opt = getopt_long(agrc, argv, "123456", options, NULL)) != -1) {
        switch (opt) {
            case '1':
                cmd_execve();
                break;
            case '2':
                cmd_execle();
                break;
            case '3':
                cmd_execlp();
                break;
            case '4':
                cmd_execvp();
                break;
            case '5':
                cmd_execv();
                break;
            case '6':
                cmd_execl();
                break;
            default:
                usage(argv[0]);
        }
    } else {
        usage(argv[0]);
    }

    return 0;
}
