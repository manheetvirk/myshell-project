#ifndef PARSE_H
#define PARSE_H

#define MAX_TOKENS 128

struct command {
    char **argv;
    char *in_file;
    char *out_file;
    int append;
    int background;
};

struct pipeline {
    struct command *left;
    struct command *right; /* NULL if no pipe */
};

struct pipeline *parse_line(const char *line);
void free_pipeline(struct pipeline *p);

#endif

