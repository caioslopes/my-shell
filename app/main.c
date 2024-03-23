#include "lib/shell.h"

int main(){

    Queue commands;
    init(&commands);

    char string[MAX_ARGS];
    char string2[MAX_ARGS];
    char string3[MAX_ARGS];

    prompt();
    input(string);

    prompt();
    input(string2);

    prompt();
    input(string3);

    enqueue(commands, string);
    enqueue(commands, string2);
    enqueue(commands, string3);
    
    for(int i = 0; i < 3; i++){
        printf("dequeue: %s\n", dequeue(commands));
    }

    return 0;
}