#Makefile compiler
# File:   main.c
# Author(s): Augusto G Serrano, Caio S Lopes. 
# Created on 20 de março de 2024.

SRC = ./app/main.c ./app/src/*.c

SOURCE = 	./app/main.c \
			./app/src/alias.c \
			./app/src/list.c \
			./app/src/queue.c \
			./app/src/shell.c \

NAME = my-shell

CC = gcc

LIB	= 	-I./app/lib/

macos	: 	$(SRC)
				$(CC) $(SRC) $(LIB) -o $(NAME)

linux	: 
			$(CC) -o $(NAME) $(SOURCE) $(LIB)