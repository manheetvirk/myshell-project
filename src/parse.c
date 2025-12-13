#include <stdlib.h>
#include <string.h>

#include "parse.h"

static char *dup_token(const char *s) {
    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

static struct command *new_cmd(void) {
    struct command *c = calloc(1, sizeof(*c));
    c->argv = calloc(MAX_TOKENS, sizeof(char *));
    return c;
}

struct pipeline *parse_line(const char *line) {
    struct pipeline *p = calloc(1, sizeof(*p));
    struct command *cur = new_cmd();
    p->left = cur;

    char *copy = dup_token(line);
    char *tok = strtok(copy, " \t\n");
    int argc = 0;

    while (tok) {
        if (strcmp(tok, "|") == 0) {
            p->right = new_cmd();
            cur->argv[argc] = NULL;
            cur = p->right;
            argc = 0;
        } else if (strcmp(tok, ">") == 0 || strcmp(tok, ">>") == 0) {
            cur->append = (tok[1] == '>');
            tok = strtok(NULL, " \t\n");
            cur->out_file = dup_token(tok);
        } else if (strcmp(tok, "<") == 0) {
            tok = strtok(NULL, " \t\n");
            cur->in_file = dup_token(tok);
        } else if (strcmp(tok, "&") == 0) {
            cur->background = 1;
        } else {
            cur->argv[argc++] = dup_token(tok);
        }
        tok = strtok(NULL, " \t\n");
    }
    cur->argv[argc] = NULL;

    free(copy);
    return p;
}

void free_pipeline(struct pipeline *p) {
    struct command *cmds[2] = {p->left, p->right};
    for (int i = 0; i < 2; i++) {
        if (!cmds[i]) continue;
        for (int j = 0; cmds[i]->argv[j]; j++)
            free(cmds[i]->argv[j]);
        free(cmds[i]->argv);
        free(cmds[i]->in_file);
        free(cmds[i]->out_file);
        free(cmds[i]);
    }
    free(p);
}

