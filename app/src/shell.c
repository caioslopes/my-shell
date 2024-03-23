#include "../lib/shell.h"

void prompt(){
    struct tm *time = get_time();
    printf("%s@%s[%d:%d:%d] %s $ ", get_username(), get_hostname(), time->tm_hour, time->tm_min, time->tm_sec, get_dir());
}

void input(char* string){
    fgets(string, MAX_ARGS, stdin);
    string[strcspn(string, "\n")] = 0;
    fflush(stdin);
}

void externs(char *args[]){
    int status;
    if(fork() != 0){
        waitpid(-1, &status, 0);
    }else{
        if(!execvp(args[0], args))
            perror("execvp");
            _exit(0);
    }
}

bool interns(char *args[], Queue commands){
    bool retorno = false;

    if(!strcmp(args[0], "exit")) { 
        _exit(0);
        retorno = true; 
    }else if(!strcmp(args[0], "cd")) { 
        chdir(args[1]);
        retorno = true;  
    }else if(!strcmp(args[0], "history")){
        history(commands);
        retorno = true;
    }
    
    return retorno;
}

void history(Queue commands){
    int size = get_size(commands);

    for(int i = 0; i < size; i++){
        char *aux;
        aux = dequeue(commands);
        enqueue(commands, aux);
        printf("%d: %s\n", i+1, aux);
    }
}

/* Envoirment */

char* get_username(){
    return getenv("USER");
}

char* get_hostname(){
    char* host = malloc(sizeof(char) * BUFFER);
    gethostname(host, BUFFER);
    return host;
}

struct tm* get_time(){
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    return tm_struct;
}

char* get_dir(){
    char cwd[BUFFER], *c = malloc(sizeof(char) * BUFFER);
    getcwd(cwd, sizeof(cwd));
    snprintf(c, BUFFER, "%s", filter_dir(cwd));
    return c;
}

/* Filters */

void filter_string(char string[], char *args[]){
    char *token;
    int count = 0;

    token = strtok(string, " ");

    do {
        args[count] = malloc(sizeof(char)*MAX_ARGS);
        snprintf(args[count], MAX_ARGS, "%s", token);
        count++;
    } while ((token = strtok(NULL, " ")));

    args[count] = NULL;
}

char* filter_dir(char cwd[]){
    char *token, *c;
    token = strtok(cwd, "/");
    do {
        snprintf(c, BUFFER, "%s", token);
    } while ((token = strtok(NULL, "/")));
    return c;
}