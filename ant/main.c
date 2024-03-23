#include "shell.h"

struct machine{
    char *username;
    char hostname[MAX_LINE];
    struct tm *time;
    char *dir;
};

int main(){
    /* Machine info */
    Machine m;
    m = malloc(sizeof(struct machine));

    /* Queue */
    Queue queue;
    init(&queue);

    /* Args */
    char *args[MAX_LINE];
    int status;

    get_userhost(m);
    get_username(m);

    while (true){
        prompt(args, m, queue);
        if(!interns(args[0], args, queue)){
            if(fork() != 0){
                waitpid(-1, &status, 0);
            }else{
                read_command(args[0], args);
            }
        }
    }
    
    return 0;
}

void prompt(char *args[], Machine m, Queue q){
    char string[MAX_LINE];
    int count = 0;

    get_time(m);
    get_dir(m);

    printf("%s@%s[%d:%d:%d] %s $ ", m->username, m->hostname,m->time->tm_hour, m->time->tm_min, m->time->tm_sec, m->dir);
    fgets(string, MAX_LINE, stdin);
    fflush(stdin);
    enqueue(q, string);
    filter_string(string, args);
}

void filter_string(char string[], char *args[]){
    char *token;
    int count = 0;

    string[strcspn(string, "\n")] = 0;

    token = strtok(string, " ");
    do {
        args[count] = malloc(sizeof(char)*MAX_LINE);
        snprintf(args[count], MAX_LINE, "%s", token);
        count++;
    } while ((token = strtok(NULL, " ")));

    args[count] = NULL;
}

void read_command(char *command, char *args[]){
    if(!execvp(command, args))
        perror("execvp");
        _exit(0);
}

void history(Queue queue, char *args[]){
    int s = get_size(queue);

    for(int i = 0; i < s; i++){
        char *aux;
        aux = dequeue(queue);
        printf("[%d]: %s\n", i + 1, aux);
        enqueue(queue, aux);
    }

}

bool interns(char *command, char *args[], Queue q){
    bool retorno = false;

    if(!strcmp(command, "exit")) { 
        _exit(0);
        retorno = true; 
    }else if(!strcmp(command, "cd")) { 
        chdir(args[1]);
        retorno = true;  
    }else if(!strcmp(command, "history")){
        history(q, args);
    }

    return retorno;
}

void get_username(Machine m){
    char* user;
    struct passwd *pwd = getpwuid(getuid());
    if (pwd)
        m->username = pwd->pw_name;
    else
        strcpy(m->username, "(?)");
}

void get_userhost(Machine machine){
    gethostname(machine->hostname, sizeof(machine->hostname));
}

void get_time(Machine m){
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    m->time = tm_struct;
}

void get_dir(Machine m){
    char *token, cwd[MAX_LINE];
    m->dir = malloc(sizeof(char)*MAX_LINE);

    getcwd(cwd, (sizeof(cwd)));

    token = strtok(cwd, "/");
    do {
        snprintf(m->dir, MAX_LINE, "%s", token);
    } while ((token = strtok(NULL, "/")));
}