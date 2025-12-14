#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"

int handle_builtin(char **argv) {
    if (!argv[0]) return 1;

    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0)
        exit(0);

    if (strcmp(argv[0], "cd") == 0) {
        char *path;

        if (argv[1])
            path = argv[1];
        else
            path = getenv("HOME");

        if (path == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }

        if (chdir(path) != 0) {
            perror("cd");   // 🔑 THIS was missing
        }

        return 1;
    }
    return 0;
}
