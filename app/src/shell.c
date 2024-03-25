/*
 * File:   shell.c
 * Author(s): Augusto G Serrano, Caio S Lopes. 
 *
 * Created on 20 de março de 2024.
 * 
 */

#include "shell.h"

void save_alias(char *args[], List l){
    Alias a;
    init_alias(&a);
    filter_alias(args, a);
    insert_end_list(l, a);
}

/* Shell */
void prompt(){
    struct tm *time = get_time();
    printf("%s@%s[%d:%d:%d] %s $ ", get_username(), get_hostname(), time->tm_hour, time->tm_min, time->tm_sec, get_dir());
}

void interpret(char *string, char *args[], Queue commands, List alias){
    if(hasRedirect(string)){
        redirect(string, args, commands, alias);
    }else{
        if(!interns(args, commands, alias)){
            if(!aliases(args, commands, alias)){
                externs(args);
            }
        }
    }
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

bool interns(char *args[], Queue commands, List alias){
    bool answer = false;

    if(!strcmp(args[0], "exit")) { 
        _exit(0);
        answer = true; 
    }else if(!strcmp(args[0], "cd")) { 
        chdir(args[1]);
        answer = true;  
    }else if(!strcmp(args[0], "history")){
        history(commands, alias);
        answer = true;
    }else if(!strcmp(args[0], "alias")){
        save_alias(args, alias);
        answer = true;
    }
    
    return answer;
}

bool aliases(char *args[], Queue commands, List alias){
    bool answer = false;
    if(!is_empty_list(alias)){
        Typeinfo a = get_info(alias, args[0]);
        if(a != NULL){
            char *args_aux[MAX_ARGS];
            filter_string(get_string(a), args_aux, " ");
            interpret(get_string(a), args_aux, commands, alias);
            answer = true;
        }
    }
    return answer;
}

void history(Queue commands, List alias){
    int size = get_size(commands);

    for(int i = 0; i < size; i++){
        char *aux;
        aux = dequeue(commands);
        enqueue(commands, aux);
        printf("%d  %s\n", i+1, aux);
    }

    char *string = malloc(sizeof(char) * BUFFER);
    prompt();
    input(string);

    string = strtok(string, "!");
    int n = atoi(string);

    char *args[BUFFER];

    for(int i = 0; i < size && i != n; i++){
        char *aux;
        aux = dequeue(commands);
        enqueue(commands, aux);
        if(i == n-1){
            filter_string(aux, args, " ");
            enqueue(commands, aux);
            interpret(string, args, commands, alias);
        }
    }
    
}

bool hasRedirect(char *string){ 
    return strchr(string, '>') != NULL;
}

int redirect(char *string, char *args[],  Queue commands, List alias){
    filter_string(string, args, ">");

    char *filename = malloc(sizeof(char)*BUFFER);
    strcpy(filename, args[1]);
    filename++;

    int out = open(filename, O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == out) { perror("opening cout.log"); return 255; }

    int save_out = dup(fileno(stdout));

    if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }

    char *down_args[MAX_ARGS];
    filter_string(args[0], down_args, " ");

    interpret(args[0], down_args, commands, alias);

    fflush(stdout); close(out);

    dup2(save_out, fileno(stdout));

    close(save_out);

    return 0;
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
void filter_string(char *string, char *args[], char *caracter){
    char *token, *temp = malloc(sizeof(char) * BUFFER);
    int count = 0;

    strcpy(temp, string);

    token = strtok(temp, caracter);

    do {
        args[count] = malloc(sizeof(char)*MAX_ARGS);
        snprintf(args[count], MAX_ARGS, "%s", token);
        count++;
    } while ((token = strtok(NULL, caracter)));

    args[count] = NULL;
}

char* filter_dir(char cwd[]){
    char *token, *c;
    token = strtok(cwd, "/");

    if(token == NULL){
        return "/";
    }

    do {
        snprintf(c, BUFFER, "%s", token);
    } while ((token = strtok(NULL, "/")));
    return c;
}

void filter_alias(char *args[], Alias alias){
    char *token, *temp = malloc(sizeof(char)*BUFFER);
    int count = 0;
    
    token = strtok(args[1], "=");
    do {
        if(!count){
            set_nickname(alias, token);
            /* snprintf(alias->nickname, BUFFER, "%s", token); */
        }else{
            strcat(temp, token);
        }
        count++;
    } while ((token = strtok(NULL, "=")));

    for(int i = 2; args[i] != NULL; i++){
        strcat(temp, " ");
        strcat(temp, args[i]);
    }

    token = strtok(temp, "\"");
    do{
        set_string(alias, token);
        /* snprintf(alias->string, BUFFER, "%s", token); */
    }while((token = strtok(NULL, "\"")));
}