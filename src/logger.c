#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "logger.h"

static int logfd;

void logger_init() {
    logfd = open("myshell.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
}

void log_command(pid_t pid, char *cmd, int status) {
    char buf[256];
    int n = snprintf(buf, sizeof(buf),
        "[pid=%d] cmd=\"%s\" status=%d\n", pid, cmd, status);
    write(logfd, buf, n);
}
