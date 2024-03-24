#include "lib/shell.h"

int main(){

    Queue commands;
    init(&commands);

    while(true){
        char *string = malloc(sizeof(char) * BUFFER);
        char *args[MAX_ARGS];

        prompt();
        input(string);
        
        filter_string(string, args);

        enqueue(commands, string);
        
        interpret(args, commands);
    }

    return 0;
}