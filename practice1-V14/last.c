#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFSIZE 4096

int main(int argc, char *argv[]) {
    int num_lines = 10;
    bool reverse = false;
    int opt;

    while ((opt = getopt(argc, argv, "n:r")) != -1) {
        switch (opt) {
            case 'n':
                num_lines = atoi(optarg);
                if (num_lines <= 0) {
                    fprintf(stderr, "Incorrect value for -n: %s\n", optarg);
                    return EXIT_FAILURE;
                }
                break;
            case 'r':
                reverse = true;
                break;
            default:
                fprintf(stderr, "Using: %s [-n number] [-r] [file]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    FILE *fp = stdin;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (!fp) {
            perror("File opening error");
            return EXIT_FAILURE;
        }
    }

    char **buffer = malloc(num_lines * sizeof(char *));
    if (!buffer) {
        perror("Memory allocation error");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_lines; i++) {
        buffer[i] = NULL;
    }

    char line[BUFSIZE];
    int count = 0;

    while (fgets(line, BUFSIZE, fp)) {
        char *copy = strdup(line);
        if (!copy) {
            perror("Memory allocation error");
            return EXIT_FAILURE;
        }
        int pos = count % num_lines;
        if (buffer[pos]) {
            free(buffer[pos]);
        }
        buffer[pos] = copy;
        count++;
    }

    if (fp != stdin) {
        fclose(fp);
    }

    int total = (count < num_lines) ? count : num_lines;
    int start = (count >= num_lines) ? count % num_lines : 0;

    if (!reverse) {
        for (int i = 0; i < total; i++) {
            int idx = (start + i) % num_lines;
            if (buffer[idx]) {
                fputs(buffer[idx], stdout);
            }
        }
    } else {
        for (int i = total - 1; i >= 0; i--) {
            int idx = (start + i) % num_lines;
            if (buffer[idx]) {
                fputs(buffer[idx], stdout);
            }
        }
    }

    for (int i = 0; i < num_lines; i++) {
        free(buffer[i]);
    }
    free(buffer);

    return 0;
}
