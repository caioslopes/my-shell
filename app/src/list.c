#include "list.h"

struct node{
    //Informação que é armazenada no node.
    Typeinfo info;  
    //Ponteiro para o próximo node.
    Node next;
};

struct lse{
    //Ponteiro para o primeiro node da lista.
    Node head;
};

void init_list(List* list){
    *list = malloc(sizeof(struct lse));
    (*list)->head = NULL;
}

void destroy_list(List* list){
    if( *list != NULL){
        //Lista existe, precisa ser destruída.
        if( (*list)->head != NULL){
            //Lista não está vazia, primeiro remove todos os nodes.
            Node rip;
            Node walker;
            rip = (*list)->head;
            while(rip->next != NULL){
                walker = rip->next;
                free(rip);
                rip = walker;
            }
            free(rip);
        }           
        //Lista não tem nodes, basta liberar a lista.
        free(*list);
        *list = NULL;
    }
}

bool is_empty_list(List list){
    return list->head == NULL;
}

void insert_end_list(List list, Typeinfo new_info){
    if(list != NULL){
        //Criar um novo nó.
        Node new_node = malloc(sizeof(struct node));

        //Definir os valores do novo nó.
        new_node->next = NULL;
        new_node->info = new_info;

        //Verificar se a lista está vazia
        if(list->head == NULL){
            //Lista é vazia.
            list->head = new_node;
        }else{
            //Lista não está vazia, caminha até o último nó da lista.
            Node walker = list->head;
            while(walker->next != NULL){
                walker = walker->next;
            }
            //Ultimo nó (walker) aponta para o novo nó.
            walker->next = new_node;
        }
    }
}

Typeinfo testing_return(List list){
    return list->head->info;
}

Typeinfo get_info(List list, char* nickname){
    Typeinfo answer = NULL;
    bool find = false;
    if(list != NULL){
        if(!is_empty_list(list)){
            Node walker = list->head;
            Node stalker = NULL;
            do{
                stalker = walker;
                if(!strcmp(get_nickname(stalker->info), nickname)){
                    answer = stalker->info;
                    find = true;
                }
                walker = walker->next;
            }while (stalker->next != NULL && !find);

        }
    }
    return answer;
}