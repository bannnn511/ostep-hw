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
    FILE *fd = fopen("./3.txt", "w+");
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
        write_to_file(fd, "hello\n");
    } else {
        wait(NULL);
        write_to_file(fd, "goodbye\n");
    }
    return 0;
}
