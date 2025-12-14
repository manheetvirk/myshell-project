#include <sys/types.h>
#ifndef LOGGER_H
#define LOGGER_H
void logger_init();
void log_command(pid_t pid, char *cmd, int status);
#endif
