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

    /* Username */
    char *user;
    user = (char *)malloc(10*sizeof(char));
    user = getlogin(); 

    /* Hostname */
    char host[256];
    int hostid;
    hostid = gethostname(host, sizeof(host));

    /* LocalTime */
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    int hour = tm_struct->tm_hour;
    int min = tm_struct->tm_min;
    int sec = tm_struct->tm_sec;

    printf("%s@%s[%d:%d:%d] $ ", user,host,hour,min,sec);
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