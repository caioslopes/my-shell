#include "shell.h"

int main(){
    char *command;
    char *args[MAX_LINE];
    int status;

    while (true){
        prompt(&command, args);

        if(strcmp(&(*command), "exit") == 0){
            exit(EXIT_SUCCESS);
        } else{
            if(fork() != 0){
                waitpid(-1, &status, 0);
            }else{
                read_command(&command, args);
            }
        }      

    }
    
    return 0;
}

void prompt(char **command, char **args[]){
    char *token, string[MAX_LINE];
    int count = 0;

    printf("%s@%s[%d:%d:%d] $ ",get_username(),get_userhost(),get_time()->tm_hour,get_time()->tm_min,get_time()->tm_sec);
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