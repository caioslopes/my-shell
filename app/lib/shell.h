#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "queue.h"

#define MAX_ARGS 200
#define BUFFER 200

void prompt();

void input(char string[]);

bool interns();

void externs();

void history();

/* Envoirment */
char* get_username();

char* get_hostname();

struct tm* get_time();

char* get_dir();

char* filter_dir(char cwd[]);