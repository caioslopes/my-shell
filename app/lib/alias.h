/*
 * File:   alias.h
 * Author(s): Augusto G Serrano, Caio S Lopes. 
 *
 * Created on 20 de março de 2024.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct alias* Alias;

void init_alias(Alias *alias);

char* get_nickname(Alias alias);

char* get_string(Alias alias);

void set_nickname(Alias alias, char* token);

void set_string(Alias alias, char* token);