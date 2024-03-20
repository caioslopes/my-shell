#include "shell.h"

int main(){
    char *command;
    char *args[MAX_LINE];

    type_prompt(&command, args);
    
    read_command(&command, args);

    return 0;
}

void type_prompt(char **command, char **args[]){
    char *token, string[MAX_LINE];
    int count = 0;

    printf("Digite um comando shell: \n");
    fgets(string, MAX_LINE, stdin);

    string[strcspn(string, "\n")] = 0;

    token = strtok(string, " ");
    do {
        if (count == 0) {
            *command = token;
        }
        args[count] = (char**) token;
        count++;
    } while ((token = strtok(NULL, " ")));

    args[count] = NULL;
}

void read_command(char **command, char **args[]){
    execvp(*command, args);
    perror("execvp");
}