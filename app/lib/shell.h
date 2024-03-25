#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "queue.h"
#include "alias.h"
#include "list.h"

#define MAX_ARGS 200
#define BUFFER 200

/* Alias */
void save_alias(char *args[], List alias);

/* Shell */
void prompt();

void input(char *string);

void interpret(char *string, char *args[], Queue commands, List alias);

bool interns(char *args[], Queue commands, List alias);

void externs(char *args[]);

bool aliases(char *args[], Queue commands, List alias);

void history(Queue commands, List alias);

bool hasRedirect(char *string);

int redirect(char *string, char *args[]);

/* Envoirment */
char* get_username();

char* get_hostname();

struct tm* get_time();

char* get_dir();

/* Filters */
void filter_string(char *string, char *args[], char *caracter);

char* filter_dir(char cwd[]);

void filter_alias(char *args[], Alias alias);