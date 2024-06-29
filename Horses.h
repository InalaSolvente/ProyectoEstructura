#ifndef HORSES_H
#define HORSES_H

#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "hashmap.h"

#define H_NUM 5

void makeHorses(horse horses[H_NUM], HashMap* horseMap);// Función principal para crear los caballos
void printHorses(horse horses[H_NUM]);// Función para imprimir la información de los caballos
bool loadHorseNames(HashMap* horseMap, const char* filename);// Función para cargar nombres de caballos desde un archivo
const char* findUnusedName(const char** names, bool* used, int size);// Función para encontrar un nombre de caballo no utilizado

#endif