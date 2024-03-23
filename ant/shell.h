#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include "queue.h"

#define MAX_LINE 1024

typedef struct machine* Machine;

void prompt(char *args[], Machine m, Queue q);

void filter_string(char string[], char *args[]);

void read_command(char *command, char *args[]);

void history(Queue queue, char *args[]);

bool interns(char *command, char *args[], Queue q);

void get_username(Machine m);

void get_userhost(Machine m);

void get_time(Machine m);

void get_dir(Machine m);
