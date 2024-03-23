#Makefile compiler

SRC = ./app/main.c ./app/src/*.c

NAME = my-shell

CC = gcc

LIBRARY_PATH	= 	-I./app/lib/

macos	: 	$(SRC)
			$(CC) $(SRC) $(LIBRARY_PATH) -o $(NAME)