#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


#define errExit(msg)                                                           \
    do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
    } while (0)

static volatile sig_atomic_t sig_flag = 0;

static void sighandler() {
    sig_flag = 1;
}

static void wait_for_signal() {
    fprintf(stdout, "wait with signal\n");

    sigset_t orgiMask, blockMask;

    // 1. block SIGUSR1 and save the original process signal mask.
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &blockMask, &orgiMask) == -1) {
        errExit("failed to sigprocmask");
    }

    // 2. SIGUSR1 signal handler
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = sighandler;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        errExit("failed to sigaction");
    }


    // 3. main flow
    const pid_t pid = fork();
    if (pid < 0) {
        errExit("failed to fork");
    }
    if (pid == 0) {
        printf("child says hello\n");
        kill(getppid(), SIGUSR1); // send signal to parent.
    } else {
        while (sig_flag == 0) {
            sigsuspend(&orgiMask);
        }
        printf("parent says goodbye\n");
    }
}

static void wait_for_pipe() {
    fprintf(stdout, "wait with pipe\n");

    int dummy;
    int pfd[2]; /* Pipe file descriptors */
    if (pipe(pfd) == -1) {
        errExit("pipe");
    }

    const pid_t pid = fork();
    if (pid < 0) {
        errExit("failed to fork");
    }
    if (pid == 0) {
        // read end is unused
        if (close(pfd[0]) == -1) {
            errExit("close");
        }
        printf("child says hello\n");
        if (close(pfd[1]) == -1) {
            errExit("close");
        }
    } else {
        // write end is unused
        if (close(pfd[1]) == -1) {
            errExit("close");
        }

        // wait for child
        if (read(pfd[0], &dummy, 1) == -1) {
            errExit("close");
        }
        printf("parent says goodbye\n");
    }
}


_Noreturn static void usage(char *name) {
    fprintf(stderr, "Usage: %s [-s|--signal] [-p|--pipe]\n", name);
    exit(EXIT_FAILURE);
}

int main(const int argc, char *argv[]) {
    int opt;
    struct option options[] = {
        {"signal", no_argument, NULL, 's'},
        {"pipe",no_argument, NULL, 'p'},
    };
    if ((opt = getopt_long(argc, argv, "sp", options, NULL)) != 1) {
        switch (opt) {
            case 's':
                wait_for_signal();
                break;
            case 'p':
                wait_for_pipe();
                break;
            default:
                usage(argv[0]);
        }
    } else {
        usage(argv[0]);
    }

    return 0;
}
