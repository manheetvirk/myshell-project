#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "execute.h"
#include "builtin.h"
#include "signals.h"
#include "logger.h"

int main() {
    char line[1024];
    setup_signals();
    logger_init();

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;
        if (strcmp(line, "\n") == 0)
            continue;

	line[strcspn(line,"\n")] = 0;

        Command *cmd = parse_input(line);

        if (!handle_builtin((*cmd).argv))
            execute_command(cmd, line);

        free_command(cmd);
    }
    return 0;


}
