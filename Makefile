CC=gcc
CFLAGS=-Wall -Wextra -g
SRC=src/*.c
INC=-Iinclude

myshell:
	$(CC) $(CFLAGS) $(INC) $(SRC) -o myshell

clean:
	rm -f myshell myshell.log
