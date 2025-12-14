# myshell-project
Authors: Manheet Kaur Virk,
        Jayla Porter,
        Dapinderdeep Kaur
        
Course: CS 12600 - 001 System Programming in C
# Overview
A minimal Unix shell built in C for academic use. This program provides core shell function without fully re-implenting Bash.

The program demonstrates multiple programming concepts such as external commands, I/O redirection, pipes, background jobs, built-ins (cd, exit), signal handling, 
and command logging. Designed for Valgrind clean and automated testing.

## Features
Execution of external commands through fork and execvp. Foreground and background job control. Built in commands such as cd[path], exit and quit. Input and output redirection. Single pipeline support. Signal handling. Command logging to myshell.log using system call write(). Dynamic memory allocation through use of malloc() and free(). Multi-file project structure through Makefile support. Clean execution using Valgrind to prevent memory leaks or invalid access. 

## Build Instructions
In order to build this program, Linux and GCC are needed. To build the shell run the make command. Once ran, it will compile all source files and produce myshell.

## Run Instructions
Our shell can be ran by running the ./myshell executable through the project directory.

## Sample Commands
ls
ls -1
grep main *.c
sleep 3 &
echo hello > out.txt
cat < out.txt
echo "one two three" | wc -w
cd /tmp
exit

## Limitations 
Only can handle a single pipe. No support for command history or tab completion. No support for quoting or environment variable expansion. Not intended to replace Bash.

