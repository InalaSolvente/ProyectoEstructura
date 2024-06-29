#include "Horses.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

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
    return "Caballo Sin Nombre";
}

void makeHorses(horse horses[H_NUM], HashMap* horseMap) {
    horses[0].amountBet = 0;
    horses[0].distance = 0;
    strcpy(horses[0].name, "");
    horses[0].winChance = 0;

    srand(time(NULL));

    // Crear arreglos para los nombres de caballos y su estado de uso
    int horseNameCount = 0;
    const char* horseNames[horseMap->capacity];
    bool used[horseMap->capacity];
    // Inicializar el arreglo 'used' a false
    for (int i = 0; i < horseMap->capacity; i++) {
        used[i] = false;
    }

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
    int minChance = 15; // Porcentaje mínimo para cada caballo

    for (int i = 1; i < H_NUM; i++) {
        horses[i].amountBet = 0;
        horses[i].distance = 0;
        strcpy(horses[i].name, findUnusedName(horseNames, used, horseNameCount));

        if (i == H_NUM - 1) {
            horses[i].winChance = remainingChance;
        } else {
            int maxChance = (remainingChance - minChance * (H_NUM - i - 1)) / 2;
            maxChance = (maxChance > 50) ? 50 : maxChance; // Asegurarse de que no supere el 50%
            maxChance = (maxChance < minChance) ? minChance : maxChance; // Asegurarse de que no sea menor que el mínimo
            horses[i].winChance = (rand() % (maxChance - minChance + 1)) + minChance;
        }
        remainingChance -= horses[i].winChance;
    }
}

void printHorses(horse horses[H_NUM]) {
    for (int i = 1; i < H_NUM; i++) {
        printf("Carril %d: %s [PdV: %i%%, $%.2f de dinero apostado]\n", 
               i,
               horses[i].name, 
               horses[i].winChance, 
               horses[i].amountBet);
    }
}

bool loadHorseNames(HashMap* horseMap, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }
    char name[100];
    while (fgets(name, sizeof(name), file)) {
        name[strcspn(name, "\n")] = 0;  // Remove newline
        addUser(horseMap, name, "");  // Using addUser function to add horse names
    }
    fclose(file);
    return true;
}