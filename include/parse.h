#ifndef PARSE_H
#define PARSE_H

typedef struct {
    char **argv;
    char **argv2;
    char *infile;
    char *outfile;
    int append;
    int background;
    int has_pipe;
} Command;

Command *parse_input(char *line);
void free_command(Command *cmd);

#endif
