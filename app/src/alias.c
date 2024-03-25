#include "alias.h"

struct alias
{
    char *nickname;
    char *string;
};

void init_alias(Alias *alias){
    Alias a;
    a = malloc(sizeof(alias));
    a->nickname = malloc(sizeof(char)*200);
    a->string = malloc(sizeof(char)*200);
    *alias = a;
}

char* get_nickname(Alias alias){
    return alias->nickname;
}

char* get_string(Alias alias){
    return alias->string;
}

void set_nickname(Alias alias, char* token){
    snprintf(alias->nickname, 200, "%s", token);
}

void set_string(Alias alias, char* token){
    snprintf(alias->string, 200, "%s", token);
}