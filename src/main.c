#include "shell.h"

int main(){
    char *command;
    char *args[MAX_LINE];

    type_prompt(command, args);

    return 0;
}

void type_prompt(char *command, char *args[]){
    char *token, string[MAX_LINE];
    int count = 0;

    printf("Digite um comando shell: \n");
    fgets(string, MAX_LINE, stdin);
    fflush(stdin);

    string[strcspn(string, "\n")] = 0;

    token = strtok(string, " ");
    do{
        if(count == 0){
            command = token;
        }
        args[count] = token;
        count++;
        /* printf("%s|", token); */
    }while((token = strtok(NULL, " ")));

    /* printf("\ncount: %d\n", count); */

    args[count] = NULL;
    args[count+1] = "\0";

    /* for(int i = 0; i < count; i++){
        printf("%s |", args[i]);
    } */

    execvp(command, args);
    perror("execvp");
}