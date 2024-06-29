#ifndef HORSES_H
#define HORSES_H

#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "hashmap.h"

#define H_NUM 5

void makeHorses(horse horses[H_NUM], HashMap* horseMap);
void printHorses(horse horses[H_NUM]);
bool loadHorseNames(HashMap* horseMap, const char* filename);

// FunciÃ³n auxiliar para encontrar un nombre no usado
const char* findUnusedName(const char** names, bool* used, int size);

#endif