#Makefile compiler
# File:   main.c
# Author(s): Augusto G Serrano, Caio S Lopes. 
# Created on 20 de março de 2024.

SRC = ./app/main.c ./app/src/*.c

NAME = my-shell

CC = gcc

LIBRARY_PATH	= 	-I./app/lib/

macos	: 	$(SRC)
			$(CC) $(SRC) $(LIBRARY_PATH) -o $(NAME)