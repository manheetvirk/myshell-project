#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <stddef.h>
#include "signals.h"

/*
 * Handles SIGCHLD and cleans up terminated child processes
 * to prevent zombie processes.
 */
static void cleanup_children(int sig)
{
    (void)sig;
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0) {
    }

    errno = saved_errno;
}

/*
 * Sets up signal handling for myshell
 */
void setup_signals(void)
{
    struct sigaction sa;

    signal(SIGINT, SIG_IGN);

    sa.sa_handler = cleanup_children;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    sigaction(SIGCHLD, &sa, NULL);
}
