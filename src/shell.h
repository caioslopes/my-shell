#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE 1000

void type_prompt(char *command, char *args[]);

void read_command(char *command, char *args[]);

