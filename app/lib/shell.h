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

/* Alias */
typedef struct alias* Alias;

void init_alias(Alias *alias);

void save_alias(char *args[]);

/* Shell */
void prompt();

void input(char *string);

void interpret(char *args[], Queue commands);

bool interns(char *args[], Queue commands);

void externs(char *args[]);

void history(Queue commands);

/* Envoirment */
char* get_username();

char* get_hostname();

struct tm* get_time();

char* get_dir();

/* Filters */
void filter_string(char *string, char *args[]);

char* filter_dir(char cwd[]);

void filter_alias(char *args[], Alias alias);