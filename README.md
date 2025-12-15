# myshell
**Authors:** Manheet Kaur Virk,
          Dapinderdeep Kaur,
        Jayla Porter
        
        
**Course:** CS 12600 - 001 System Programming in C

**Semester:** Fall 2025
# Overview
This project implements a small Unix shell in C. It handles external commands, redirection, pipes, background processes, and built‑ins like cd and exit. It also works well with signal handling for SIGINT and SIGCHLD, along with command logging. The shell uses dynamic memory and passes  Valgrind with no leaks.

## Features
- Runs external commands using fork() and execvp()
- Supports both foreground and background jobs
- Includes built‑in commands: cd, exit, and quit
- Handles input and output redirection (<, >, >>)
- Supports a single pipe between two commands (cmd1 | cmd2)
- Implements signal handling for SIGINT and SIGCHLD
- Logs external commands to myshell.log using write()
- Uses dynamic memory (malloc/free) with no leaks under Valgrind
- Organized as a multi‑file project with a Makefile

## Build Instructions
This project requires Linux and GCC. To build the shell, use the command:

```bash
make
```

This will compile all source files and produce the myshell executable.
## Run Instructions
To start the shell interactively:

./myshell

The shell displays the prompt:

myshell>

## Project Structure
- src/
  - main.c
  - parse.c
  - execute.c
  - builtin.c
  - signals.c
  - logger.c
- include/
  - parse.h
  - execute.h
  - builtin.h
  - signals.h
  - logger.h
- Makefile
- README.md

## Sample Commands
- ls
- ls -l
- grep char include/parse.h
- sleep 3 &
- sleep 1
- echo hello > out.txt
- cat < out.txt
- echo "one two three" | wc -w
- echo "one two three" | wc -l
- cd /tmp
- pwd
- exit

## Limitations 
The shell can only handle a single pipe between two commands, and it does not support things like command history or tab completion. It does not implement handling quoting or environment variable expansion. Overall, this shell is a minimal course project and not a full Bash replacement.



