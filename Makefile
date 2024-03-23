#Makefile compiler

SRC = ./app/main.c ./app/src/*.c

NAME = ourShell

CC = gcc

LIBRARY_PATH	= 	-I./app/lib/

macos	: 	$(SRC)
			$(CC) $(SRC) $(LIBRARY_PATH) -o $(NAME)