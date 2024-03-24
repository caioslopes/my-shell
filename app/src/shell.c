#include "../lib/shell.h"

/* Alias */
struct alias
{
    char *nickname;
    char *string;
};


void init_alias(Alias *alias){
    Alias a;
    a = malloc(sizeof(alias));
    a->nickname = malloc(sizeof(char)*BUFFER);
    a->string = malloc(sizeof(char)*BUFFER);
    *alias = a;
}

void save_alias(char *args[]){
    Alias a;
    init_alias(&a);
    filter_alias(args, a);

    printf("nickname: %s\n", a->nickname);
    printf("string: %s\n", a->string);
}

/* Shell */
void prompt(){
    struct tm *time = get_time();
    printf("%s@%s[%d:%d:%d] %s $ ", get_username(), get_hostname(), time->tm_hour, time->tm_min, time->tm_sec, get_dir());
}

void interpret(char *args[], Queue commands){
    if(!interns(args, commands)){
        externs(args);
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
    }else if(!strcmp(args[0], "alias")){
        save_alias(args);
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
            filter_string(aux, args);
            enqueue(commands, aux);
            interpret(args, commands);
        }
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
void filter_string(char *string, char *args[]){
    char *token, *temp = malloc(sizeof(char) * BUFFER);
    int count = 0;

    strcpy(temp, string);

    token = strtok(temp, " ");

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

void filter_alias(char *args[], Alias alias){
    char *token, *temp = malloc(sizeof(char)*BUFFER);
    int count = 0;
    
    token = strtok(args[1], "=");
    do {
        if(!count){
            snprintf(alias->nickname, BUFFER, "%s", token);
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
        snprintf(alias->string, BUFFER, "%s", token);
    }while((token = strtok(NULL, "\"")));
}