#ifndef HORSES_H
#define HORSES_H

#include <stdlib.h>
#include "structs.h"
#include "hashmap.h"

#define H_NUM 5
#define H1_CHANCE 50
#define H2_CHANCE 70
#define H3_CHANCE 85

void makeHorses(horse horses[H_NUM], HashMap* horseMap);
const char* nameHorse(HashMap* horseMap);
void printHorses(horse horses[H_NUM]);
bool loadHorseNames(HashMap* horseMap, const char* filename);

#endif 