#include "lib/shell.h"

void insert_queue(Queue commands, char *string);

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

        insert_queue(commands, string);

        interpret(string, args, commands, alias);
    }

    return 0;
}

void insert_queue(Queue commands, char *string){
    if(is_full(commands)){ dequeue(commands); }
    enqueue(commands, string);
}