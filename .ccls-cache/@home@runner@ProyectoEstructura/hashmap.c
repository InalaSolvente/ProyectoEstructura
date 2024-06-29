#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_MULTIPLIER 65599

unsigned long hashString(const char* str) {
  unsigned long hash = 0;
  while (*str) {
    hash = hash * HASH_MULTIPLIER + *str++;
  }
  return hash;
}

HashMap* createHashMap(int capacity) {
  HashMap* map = (HashMap*)malloc(sizeof(HashMap));
  map->buckets = (Node**)calloc(capacity, sizeof(Node*));
  map->capacity = capacity;
  return map;
}

void freeHashMap(HashMap* map) {
  for (int i = 0; i < map->capacity; i++) {
    Node* current = map->buckets[i];
    while (current != NULL) {
      Node* temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(map->buckets);
  free(map);
}

bool addUser(HashMap* map, const char* username, const char* password) {
  unsigned long hash = hashString(username) % map->capacity;
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->user.username, username);
  strcpy(newNode->user.password, password);
  newNode->user.balance = 0.0;
  newNode->next = NULL;

  if (map->buckets[hash] == NULL) {
    map->buckets[hash] = newNode;
  } else {
    Node* current = map->buckets[hash];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
  return true;
}

bool loadUsers(HashMap* map, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return false;
  }

  char line[100];
  while (fgets(line, sizeof(line), file)) {
    char username[40], password[40];
    double balance;
    sscanf(line, "%s %s %lf", username, password, &balance);
    addUser(map, username, password);
    updateUserBalance(map, username, balance);
  }

  fclose(file);
  return true;
}

bool saveUsers(HashMap* map, const char* filename) {
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    return false;
  }

  for (int i = 0; i < map->capacity; i++) {
    Node* current = map->buckets[i];
    while (current != NULL) {
      fprintf(file, "%s %s %.2f\n", current->user.username, current->user.password, current->user.balance);
      current = current->next;
    }
  }

  fclose(file);
  return true;
}

User* getUserByUsername(HashMap* map, const char* username) {
  unsigned long hash = hashString(username) % map->capacity;
  Node* current = map->buckets[hash];
  while (current != NULL) {
    if (strcmp(current->user.username, username) == 0) {
      return &(current->user);
    }
    current = current->next;
  }
  return NULL;
}

void updateUserBalance(HashMap* map, const char* username, double balance) {
  User* user = getUserByUsername(map, username);
  if (user != NULL) {
    user->balance = balance;
  }
}