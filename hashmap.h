#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

typedef struct {
  char username[40];
  char password[40];
  double balance;
} User;

typedef struct Node {
  User user;
  struct Node* next;
} Node;

typedef struct {
  Node** buckets;
  int capacity;
} HashMap;

HashMap* createHashMap(int capacity);
void freeHashMap(HashMap* map);
bool addUser(HashMap* map, const char* username, const char* password);
bool loadUsers(HashMap* map, const char* filename);
bool saveUsers(HashMap* map, const char* filename);
User* getUserByUsername(HashMap* map, const char* username);
void updateUserBalance(HashMap* map, const char* username, double balance);

#endif