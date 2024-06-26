#include "Horses.h"
#include <string.h>
#include <time.h>

void makeHorses(horse horses[H_NUM], HashMap* horseMap) {
    horses[0].amountBet = 0;
    horses[0].distance = 0;
    strcpy(horses[0].name, "");
    horses[0].winChance = 0;
    srand(time(NULL));

    int remainingChance = 100;
    for (int i = 1; i < H_NUM; i++) {
        horses[i].amountBet = 0;
        horses[i].distance = 0;
        strcpy(horses[i].name, nameHorse(horseMap));

        if (i == H_NUM - 1) {
            horses[i].winChance = remainingChance;
        } else {
            int maxChance = remainingChance / (H_NUM - i);
            horses[i].winChance = (rand() % maxChance) + 1;
        }
        remainingChance -= horses[i].winChance;
    }
}

const char* nameHorse(HashMap* horseMap) {
    int attempts = 0;
    while (attempts < horseMap->capacity) {
        int randomIndex = rand() % horseMap->capacity;
        Node* current = horseMap->buckets[randomIndex];
        while (current != NULL) {
            if (strcmp(current->user.username, "") != 0) {
                return current->user.username;
            }
            current = current->next;
        }
        attempts++;
    }
  return "Caballo Sin Nombre";
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