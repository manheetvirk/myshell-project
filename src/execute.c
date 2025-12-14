#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "logger.h"

void execute_command(Command *cmd, char *raw) {

    if ((*cmd).has_pipe) {
        int fd[2];
        if (pipe(fd) == -1) {
            perror("pipe");
            return;
        }

        pid_t p1 = fork();
        if (p1 == 0) {
            signal(SIGINT, SIG_DFL);

            if ((*cmd).infile) {
                int fd_in = open((*cmd).infile, O_RDONLY);
                if (fd_in < 0) {
                    perror((*cmd).infile);
                    exit(1);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }

            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp((*cmd).argv[0], (*cmd).argv);
            perror("exec");
            exit(1);
        }

        pid_t p2 = fork();
        if (p2 == 0) {
            signal(SIGINT, SIG_DFL);
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp((*cmd).argv2[0], (*cmd).argv2);
            perror("exec");
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);
        waitpid(p1, NULL, 0);
        waitpid(p2, NULL, 0);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);

        if ((*cmd).infile) {
            int fd = open((*cmd).infile, O_RDONLY);
            if (fd < 0) {
                perror((*cmd).infile);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if ((*cmd).outfile) {
            int fd;
            if ((*cmd).append)
                fd = open((*cmd).outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
            else
                fd = open((*cmd).outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0) { perror("open outfile"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp((*cmd).argv[0], (*cmd).argv);
        perror("exec");
        exit(1);
    }

    if (!(*cmd).background) {
        int status;
        waitpid(pid, &status, 0);
        log_command(pid, raw, status);
    } else {
        printf("[bg] started pid %d\n", pid);
    }
}
