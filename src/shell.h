#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1000

void prompt(char **command, char **args[]);

void read_command(char **command, char **args[]);

char* get_username();

char* get_userhost();

struct tm* get_time();
