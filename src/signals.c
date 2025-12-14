#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "signals.h"

void sigchld_handler(int sig) {
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void setup_signals() {
    signal(SIGINT, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
}
