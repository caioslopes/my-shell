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

    /* Command and Args */
    char *command = malloc(sizeof(char)*MAX_LINE);
    char *args[MAX_LINE];
    int status;

    get_userhost(m);
    get_username(m);

    while (true){
        prompt(command, args, m);
        if(!interns(command, args)){
            if(fork() != 0){
                waitpid(-1, &status, 0);
            }else{
                read_command(command, args);
            }
        } 
    }
    
    return 0;
}

void prompt(char *command, char *args[], Machine m){
    char *token, string[MAX_LINE];
    int count = 0;

    get_time(m);
    get_dir(m);

    printf("%s@%s[%d:%d:%d] %s $ ", m->username, m->hostname,m->time->tm_hour, m->time->tm_min, m->time->tm_sec, m->dir);
    fgets(string, MAX_LINE, stdin);
    fflush(stdin);

    string[strcspn(string, "\n")] = 0;

    token = strtok(string, " ");
    do {
        args[count] = malloc(sizeof(char)*MAX_LINE);
        snprintf(args[count], MAX_LINE, "%s", token);
        count++;
    } while ((token = strtok(NULL, " ")));

    args[count] = NULL;
    strcpy(command, args[0]);
}

void read_command(char *command, char *args[]){
    execvp(command, args);
    perror("execvp");
}

bool interns(char *command, char *args[]){
    bool retorno = false;

    if(!strcmp(command, "exit")) { 
        _exit(0);
        retorno = true; 
    }else if(!strcmp(command, "cd")) { 
        chdir(args[1]);
        retorno = true;  
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
    int hostid;
    hostid = gethostname(machine->hostname, sizeof(machine->hostname));
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