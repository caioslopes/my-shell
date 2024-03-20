#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1000

void prompt(char **command, char **args[]);

void read_command(char **command, char **args[]);

