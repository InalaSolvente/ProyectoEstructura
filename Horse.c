#include "Horses.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

// Función para encontrar un nombre de caballo no utilizado
const char* findUnusedName(const char** names, bool* used, int size) {
  int attempts = 0;
  while (attempts < size) {
    int randomIndex = rand() % size;
    if (!used[randomIndex]) {
      used[randomIndex] = true;
      return names[randomIndex];
    }
    attempts++;
  }
  // Si no se encuentra un nombre disponible, retorna un nombre por defecto
  return "Caballo Sin Nombre";
}

// Función principal para crear los caballos
void makeHorses(horse horses[H_NUM], HashMap* horseMap) {
  // Inicializar el primer elemento del arreglo de caballos (no se usa)
  horses[0].amountBet = 0;
  horses[0].distance = 0;
  strcpy(horses[0].name, "");
  horses[0].winChance = 0;

  // Inicializar el generador de números aleatorios
  srand(time(NULL));

  // Crear arreglos para los nombres de caballos y su estado de uso
  int horseNameCount = 0;
  const char* horseNames[horseMap->capacity];
  bool used[horseMap->capacity];

  // Inicializar el arreglo 'used' a false
  for (int i = 0; i < horseMap->capacity; i++) {
    used[i] = false;
  }

  // Llenar el arreglo horseNames con nombres del HashMap
  for (int i = 0; i < horseMap->capacity; i++) {
    Node* current = horseMap->buckets[i];
    while (current != NULL) {
      if (strcmp(current->user.username, "") != 0) {
        horseNames[horseNameCount] = current->user.username;
        horseNameCount++;
      }
      current = current->next;
    }
  }

  int remainingChance = 100;
  int minChance = 5; // Porcentaje mínimo para cada caballo
  int maxAllowedChance = 45; // Porcentaje máximo permitido
  bool needsRegeneration;

  // Bucle para generar porcentajes de victoria equilibrados
  do {
    needsRegeneration = false;
    remainingChance = 100;

    for (int i = 1; i < H_NUM; i++) {
      horses[i].amountBet = 0;
      horses[i].distance = 0;

      if (i == H_NUM - 1) {
        // El último caballo toma el porcentaje restante
        horses[i].winChance = remainingChance;
        if (horses[i].winChance > maxAllowedChance) {
          needsRegeneration = true;
          break;
        }
      } else {
        // Calcular el porcentaje de victoria para los demás caballos
        int maxChance = (remainingChance - minChance * (H_NUM - i - 1)) / 2;
        maxChance = (maxChance > maxAllowedChance) ? maxAllowedChance : maxChance;
        maxChance = (maxChance < minChance) ? minChance : maxChance;
        horses[i].winChance = (rand() % (maxChance - minChance + 1)) + minChance;

        if (horses[i].winChance > maxAllowedChance) {
          needsRegeneration = true;
          break;
        }
      }
      remainingChance -= horses[i].winChance;
    }
  } while (needsRegeneration);

  // Asignar nombres a los caballos después de que se hayan generado los porcentajes
  for (int i = 1; i < H_NUM; i++) {
    strcpy(horses[i].name, findUnusedName(horseNames, used, horseNameCount));
  }
}

// Función para imprimir la información de los caballos
void printHorses(horse horses[H_NUM]) {
  for (int i = 1; i < H_NUM; i++) {
    printf("Carril %d: %s [PdV: %i%%, $%.2f de dinero apostado]\n",i,horses[i].name,horses[i].winChance, horses[i].amountBet);
  }
}

// Función para cargar nombres de caballos desde un archivo
bool loadHorseNames(HashMap* horseMap, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return false;
  }
  char name[100];
  while (fgets(name, sizeof(name), file)) {
    name[strcspn(name, "\n")] = 0;  // Eliminar el salto de línea
    addUser(horseMap, name, "");  // Usar la función addUser para agregar nombres de caballos
  }
  fclose(file);
  return true;
}