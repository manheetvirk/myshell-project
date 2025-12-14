#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define MAX 64

Command *parse_input(char *line) {
    Command *cmd = malloc(sizeof(Command));

    (*cmd).argv = malloc(sizeof(char*) * MAX);
    (*cmd).argv2 = NULL;
    (*cmd).infile = NULL;
    (*cmd).outfile = NULL;
    (*cmd).append = 0;
    (*cmd).background = 0;
    (*cmd).has_pipe = 0;

    int i = 0;
    char *token = strtok(line, " \t\n");

    while (token) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            (*cmd).infile = strdup(token);
        }
        else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            (*cmd).outfile = strdup(token);
            (*cmd).append = 0;
        }
        else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t\n");
            (*cmd).outfile = strdup(token);
            (*cmd).append = 1;
        }
        else if (strcmp(token, "&") == 0) {
            (*cmd).background = 1;
        }
        else if (strcmp(token, "|") == 0) {
            (*cmd).has_pipe = 1;
            (*cmd).argv[i] = NULL;

            (*cmd).argv2 = malloc(sizeof(char*) * MAX);
            int j = 0;
            token = strtok(NULL, " \t\n");
            while (token) {
                (*cmd).argv2[j++] = strdup(token);
                token = strtok(NULL, " \t\n");
            }
            (*cmd).argv2[j] = NULL;
            return cmd;
        }
        else {
            (*cmd).argv[i++] = strdup(token);
        }
        token = strtok(NULL, " \t\n");
    }

    (*cmd).argv[i] = NULL;
    return cmd;
}

void free_command(Command *cmd) {
    for (int i = 0; (*cmd).argv[i]; i++)
        free((*cmd).argv[i]);
    free((*cmd).argv);

    if ((*cmd).argv2) {
        for (int i = 0; (*cmd).argv2[i]; i++)
            free((*cmd).argv2[i]);
        free((*cmd).argv2);
    }

    if ((*cmd).infile) free((*cmd).infile);
    if ((*cmd).outfile) free((*cmd).outfile);
    free(cmd);
}
