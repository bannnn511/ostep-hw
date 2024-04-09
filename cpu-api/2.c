#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void write_to_file(FILE *f, const char *str) {
    int c;
    for (const char *ptr = str; (c = *ptr++) != 0;) {
        fputc(c, f);
    }
}

int main() {
    FILE *fd = fopen("./2.txt", "w+");
    if (fd == NULL) {
        fprintf(stderr, "File opening failed");
        return EXIT_FAILURE;
    }

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork process failed\n");
        exit(1);
    }
    if (rc == 0) {
        write_to_file(fd, "this is child process.\n");
    } else {
        write_to_file(fd, "this is parent process.\n");
    }
    return 0;
}
