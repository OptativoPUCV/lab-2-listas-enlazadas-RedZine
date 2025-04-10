#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
    List* lista  = (List*) malloc (sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;

     return lista;
}

void * firstList(List * list) {
    list->current = list->head;
    if(list->current) return list->current->data;

    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL)
    {
        list->current = list->current->next;
    }
    if(list->current != NULL)
        return list->current->data;
    return NULL;
}

void * lastList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->tail;
    if (list->current != NULL)  return list->current->data;

    return NULL;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {

    if (list == NULL) return;

    Node *NuevoNodo = createNode(data);
    NuevoNodo->next = list->head;

    if(list->head != NULL) list->head->prev = NuevoNodo;

    list->head = NuevoNodo;

    if (list->tail == NULL) list->tail = NuevoNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {

    if(list == NULL || list->current == NULL) return;

    Node *NuevoNodo = createNode(data);
    NuevoNodo->next = list->current->next;
    NuevoNodo->prev = list->current;

    if(list->current->next != NULL) list->current->next->prev = NuevoNodo;
    else{
        list->tail = NuevoNodo;
    }

    list->current->next = NuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    Node *Aux = list->current;
    void *data = Aux->data;

    if (Aux->prev != NULL){
        Aux->prev->next = Aux->next;
    }
    else{
        list->head = Aux->next;
    }

    if(Aux->next != NULL){
        Aux->next->prev = Aux->prev;
        list->current = Aux->next;
    }
    else{
        list->tail = Aux->prev;
        list->current = Aux->prev;
    }

    free(Aux);

    if(list->head == NULL) return NULL;

    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}