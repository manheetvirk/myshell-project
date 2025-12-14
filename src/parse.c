#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define MAX 64

Command *parse_input(char *line) {
    Command *cmd = malloc(sizeof(Command));

    cmd->argv = malloc(sizeof(char*) * MAX);
    cmd->argv2 = malloc(sizeof(char*) * MAX);
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->background = 0;
    cmd->has_pipe = 0;

    int right_side = 0;   // 0 = left of pipe, 1 = right of pipe
    int i = 0, j = 0;

    char *token = strtok(line, " \t\n");

    while (token) {

        // INPUT REDIRECTION
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            if (!right_side)
                cmd->infile = strdup(token);
            token = strtok(NULL, " \t\n");
            continue;
        }

        // OUTPUT REDIRECTION >
        else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (!right_side) {
                cmd->outfile = strdup(token);
                cmd->append = 0;
            }
            token = strtok(NULL, " \t\n");
            continue;
        }

        // OUTPUT REDIRECTION >>
        else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t\n");
            if (!right_side) {
                cmd->outfile = strdup(token);
                cmd->append = 1;
            }
            token = strtok(NULL, " \t\n");
            continue;
        }

        // BACKGROUND JOB
        else if (strcmp(token, "&") == 0) {
            cmd->background = 1;
            token = strtok(NULL, " \t\n");
            continue;
        }

        // PIPE
        else if (strcmp(token, "|") == 0) {
            cmd->has_pipe = 1;
            right_side = 1;
            token = strtok(NULL, " \t\n");
            continue;
        }

        // NORMAL ARGUMENT
        else {
            if (!right_side)
                cmd->argv[i++] = strdup(token);
            else
                cmd->argv2[j++] = strdup(token);
        }

        token = strtok(NULL, " \t\n");
    }

    // NULL‑terminate argv arrays
    cmd->argv[i] = NULL;
    if (cmd->has_pipe)
        cmd->argv2[j] = NULL;
    else {
        free(cmd->argv2);
        cmd->argv2 = NULL;
    }

    return cmd;
}

void free_command(Command *cmd) {
    for (int i = 0; cmd->argv[i]; i++)
        free(cmd->argv[i]);
    free(cmd->argv);

    if (cmd->argv2) {
        for (int i = 0; cmd->argv2[i]; i++)
            free(cmd->argv2[i]);
        free(cmd->argv2);
    }

    if (cmd->infile) free(cmd->infile);
    if (cmd->outfile) free(cmd->outfile);

    free(cmd);
}
