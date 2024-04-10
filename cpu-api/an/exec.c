#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/_types/_null.h>

void
usageErr(const char *format, ...) {
    va_list argList;

    fflush(stdout); /* Flush any pending stdout */

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr); /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
    char *argVec[10];
    char *envVec[] = {"GREET=salut", "BYE=adieu", NULL};

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s pathname\n", argv[0]);
    }

    argVec[0] = strchr(argv[1], '/');
    if (argVec[0] != NULL) {
        argVec[0]++;
        printf("here %s\n", argVec[0]);
    } else
        argVec[0] = argv[1];
    argVec[1] = "hello world";
    argVec[2] = "goodby";
    argVec[3] = NULL;


    execve(argv[1], argVec, envVec);

    printf("shouldn't get here\n");
}
