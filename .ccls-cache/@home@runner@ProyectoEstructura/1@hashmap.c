#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
  unsigned long hash = 5381;
  int c;

  while ((c = *key++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap *map, char *key, void *value) {
  if (map == NULL || key == NULL) return;
  Pair *par = createPair(key, value);
  if (par == NULL) return;
  unsigned long pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL) {
    if (strcmp(map->buckets[pos]->key, key) == 0) {
      free(par);
      return;
      }
    pos = (pos + 1) % map->capacity;;
  }
  map->buckets[pos] = par;
  map->size++;
  map->current = pos;
}


void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  if (map == NULL) return;
  Pair **old_buckets = map->buckets;
  unsigned int old_capacity = map->capacity;

  map->capacity *= 2;

  // Paso c: Asignar a map->buckets un nuevo arreglo con la nueva capacidad
  map->buckets = (Pair **)malloc(map->capacity * sizeof(Pair *));
  if (map->buckets == NULL) {
    map->capacity = old_capacity; 
    return;
    }

  map->size = 0;

  for (unsigned int i = 0; i < old_capacity; i++) {
    if (old_buckets[i] != NULL && old_buckets[i]->key != NULL) {
    insertMap(map, old_buckets[i]->key, old_buckets[i]->value);
      }
    }
  free(old_buckets);
}



HashMap * createMap(long capacity) {
  HashMap *mapa = (HashMap*)malloc(sizeof(HashMap)*capacity);
  if (mapa == NULL) return NULL;
  mapa->buckets = (Pair**)malloc(sizeof(Pair*) * capacity);
  if (mapa->buckets == NULL) {
    free(mapa);
    return NULL;
  }
  for(unsigned int i = 0; i < capacity; i++){
    mapa->buckets[i] = NULL;
  }
  mapa->capacity = capacity;
  mapa->current = -1;
  mapa->size = 0;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  if(map==NULL || key==NULL) return;
  Pair *par = createPair(NULL,NULL);
  unsigned long pos = hash(key,map->capacity);
  while(map->buckets[pos]!=NULL && strcmp(map->buckets[pos]->key,key)!= 0){
    pos++;
  }
  if (pos >= map->capacity) return;
  if(map->buckets[pos]!=NULL && strcmp(map->buckets[pos]->key,key) == 0) {
    map->buckets[pos] = par;
    map->size--;
    map->current = pos;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
if(map==NULL || key==NULL) return NULL;
  unsigned long pos = hash(key,map->capacity);
  while(map->buckets[pos]!=NULL){
    if(strcmp(map->buckets[pos]->key,key) != 0) {

      pos++;
    }
    else{
      //printf("%ld %ld",map->current,pos);
      map->current = pos;
      return map->buckets[pos];
    } 
  }
  return NULL;
}

Pair * firstMap(HashMap * map) {
  if(map==NULL) return NULL;
  for(unsigned int i = 0; i < map->capacity; i++){
    if(map->buckets[i]!=NULL && map->buckets[i]->key != NULL) {
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair *nextMap(HashMap *map) {
  if (map == NULL || map->current >= map->capacity - 1) return NULL;
  map->current++;
  while ((map->current < map->capacity) && (map->buckets[map->current] == NULL || map->buckets[map->current]->key == NULL)) {
    map->current++;
  }
  return map->buckets[map->current];
}