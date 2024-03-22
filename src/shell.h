#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1024

typedef struct machine* Machine;

void prompt(char *command, char *args[], Machine m);

void read_command(char *command, char *args[]);

void interns(char *command, char *args[]);

void get_username(Machine m);

void get_userhost(Machine m);

void get_time(Machine m);

void get_dir(Machine m);
