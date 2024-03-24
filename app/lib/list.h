#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "alias.h"

typedef struct node* Node;

typedef struct lse* List;

typedef Alias Typeinfo;

void init_list(List* list);

void destroy_list(List* list);

bool is_empty_list(List list);

void insert_end_list(List list, Typeinfo new_info);

Typeinfo get_info(List list, char* nickname);

Typeinfo testing_return(List list);