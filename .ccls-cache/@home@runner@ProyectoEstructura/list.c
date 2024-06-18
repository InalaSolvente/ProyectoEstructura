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

List * createList() {
  List *lista = (List *)malloc(sizeof(List));
     return lista;
}

void * firstList(List * list) {
  if (list == NULL) return NULL;
  if (list->head == NULL) return NULL;
  Node*aux = list->head;
  return aux->data;
}

void * nextList(List * list) {
  if (list == NULL) return NULL;
  if (list->current == NULL) return NULL;
  if (list->current->next == NULL) return NULL;
  list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
  if (list == NULL) return NULL;
  if (list->head == NULL) return NULL;
  Node *aux = list->head;
  while (aux -> next != NULL){
    aux = aux -> next;}
  list->current = aux;
  return list->current->data;
}

void * prevList(List * list) {
  if (list == NULL) return NULL;
  if (list->current == NULL) return NULL;
  if (list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
  if (list == NULL) return;
  Node *nuevo = createNode(data);
  Node *aux;
  if (list->head == NULL) list->head = nuevo;
  else {
    aux = list->head;
    list->head = nuevo;
    while (aux->next != NULL){
      list->current = aux;
      list->current = list->current->next;
      aux = aux->next;
    }
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
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
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}