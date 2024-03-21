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
        interns(command, args);
        if(fork() != 0){
            waitpid(-1, &status, 0);
        }else{
            read_command(command, args);
        }
    }
    
    return 0;
}

void prompt(char *command, char *args[], Machine m){
    char *token, string[MAX_LINE];
    int count = 0;

    get_time(m);

    printf("%s@%s[%d:%d:%d] $ ", m->username, m->hostname,m->time->tm_hour, m->time->tm_min, m->time->tm_sec);
    fgets(string, MAX_LINE, stdin);
    fflush(stdin);

    string[strcspn(string, "\n")] = 0;

    token = strtok(string, " ");
    do {
        args[count] = (char*) token;
        count++;
    } while ((token = strtok(NULL, " ")));

    args[count] = NULL;
    strcpy(command, args[0]);
}

void read_command(char *command, char *args[]){
    execvp(command, args);
    perror("execvp");
}

void interns(char *command, char *args[]){
    if(!strcmp(command, "exit")) { _exit(0); }
    if(!strcmp(command, "cd")) { chdir(*args); }
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