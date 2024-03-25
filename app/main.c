/*
 * File:   main.c
 * Author(s): Augusto G Serrano, Caio S Lopes. 
 *
 * Created on 20 de março de 2024.
 * 
 */

#include "lib/shell.h"

int main(){

    Queue commands;
    init(&commands);

    List alias;
    init_list(&alias);

    while(true){
        char *string = malloc(sizeof(char) * BUFFER);
        char *args[MAX_ARGS];

        prompt();
        input(string);
        
        filter_string(string, args, " ");

        enqueue(commands, string);

        interpret(string, args, commands, alias);
    }

    return 0;
}