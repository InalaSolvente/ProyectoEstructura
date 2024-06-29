#include "hashmap.h"
#include "Horses.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define REDC printf("\033[0;31m")
#define WHITE printf("\033[0m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[0;33m")
#define CYAN printf("\033[0;36m")

#define MAX 40
#define TRACK_LENGTH 80

void limpiarPantalla() {
  printf("\033[2J\033[1;1H");
}

double login(HashMap* map, char* username);
double makeUser();
double addFunds(double oldBalance, char* username, HashMap* map);
double bet(double balance, horse horses[5]);
double watch(horse horses[5]);
void registerUser(HashMap* map, char* username);
void saveUser(double balance, char* username, HashMap* map);

int main() {
  double balance;
  char username[MAX];
  limpiarPantalla();

  puts(" ~*~*~*~*~*~*~ Bienvenido a las carreras! ~*~*~*~*~*~*~ ");

  // Crear e inicializar el mapa hash para usuarios
  HashMap* userMap = createHashMap(100);
  if (userMap == NULL) {
    fprintf(stderr, "Error: No se pudo crear el mapa de usuarios\n");
    return 1;
  }
  loadUsers(userMap, "users.txt");

  // Crear e inicializar el mapa hash para nombres de caballos
  HashMap* horseMap = createHashMap(200);
  if (horseMap == NULL) {
    fprintf(stderr, "Error: No se pudo crear el mapa de caballos\n");
    freeHashMap(userMap);
    return 1;
  }
  loadHorseNames(horseMap, "namesHorses.txt");

  horse horses[H_NUM];
  makeHorses(horses, horseMap);

  balance = login(userMap, username);
  limpiarPantalla();

  int selection = 0;
  double winnings = 0.0;

  while (1) {
    printf("Bienvenido %s! Saldo actual: %.2f\n", username, balance);

    while (1) {
      printf("\n");
      printf("Por favor ingrese el número del comando que desea ejecutar.\n");
      printf("1: Agregar fondos a la cuenta.\n");
      printf("2: Apostar por los caballos.\n");
      printf("3: Ver carrera.\n");
      printf("4: Cerrar sesión.\n");

      if (scanf(" %i", &selection)) {
        break;
      } else {
        char exit;
        if (scanf(" %c", &exit)) {
          if (exit == 'e') {
            limpiarPantalla();
            break;
          }
        }
        printf("Lo siento, esa no es una selección válida, por favor intente de nuevo.\n\n");
        while (getchar() != '\n');
      }
    }

    if (selection == 4) {
      limpiarPantalla();
      saveUser(balance, username, userMap);
      freeHashMap(userMap);
      freeHashMap(horseMap);
      return 0;
    }

    switch (selection) {
      case 1:
          balance = addFunds(balance, username, userMap);
          break;
      case 2:
          balance = bet(balance, horses);
          break;
      case 3:
          winnings = watch(horses);
          balance += winnings;
          makeHorses(horses, horseMap);
          break;
      default:
          printf("Lo siento, esa no es una selección válida, por favor intente de nuevo.\n\n");
    }
  }

  saveUser(balance, username, userMap);
  freeHashMap(userMap);
  freeHashMap(horseMap);
  return 0;
}

double login(HashMap* map, char* username) {
  char password[MAX];
  char choice;

  limpiarPantalla();
  puts(" ~*~*~*~*~*~*~ Bienvenido a las carreras! ~*~*~*~*~*~*~ ");
  puts("¿Ya tiene una cuenta? (s/n)");
  scanf(" %c", &choice);

  if (choice == 's' || choice == 'S') {
    puts("Ingrese nombre de usuario");
    scanf("%39s", username);
    puts("Ingrese contraseña");
    scanf("%39s", password);

    User* user = getUserByUsername(map, username);
    if (user && strcmp(user->password, password) == 0) {
      printf("Inicio de sesión exitoso. Bienvenido %s, su saldo es $%.2f\n", username, user->balance);
      return user->balance;
    } else {
      char retry;
      printf("Usuario o contraseña incorrectos. No se encontró la cuenta.\n");
      printf("¿Desea intentar nuevamente o registrar una nueva cuenta? (i/r): ");
      scanf(" %c", &retry);

      if (retry == 'i' || retry == 'I') {
        return login(map, username);
      } else if (retry == 'r' || retry == 'R') {
        registerUser(map, username);
        return 0.0;
      } else {
        printf("Opción no válida. Saliendo del programa.\n");
        return 0.0;
      }
    }
  } else {
    registerUser(map, username);
    return 0.0;
  }
}

void registerUser(HashMap* map, char* username) {
  char password[MAX];

  puts("Ingrese un nombre de usuario");
  scanf("%39s", username);
  puts("Ingrese una contraseña");
  scanf("%39s", password);

  if (addUser(map, username, password)) {
    printf("Usuario registrado correctamente.\n");
  } else {
    printf("Error al registrar el usuario.\n");
  }
}

double addFunds(double oldBalance, char* username, HashMap* map) {
  double change, newBalance;
  char exit;
  limpiarPantalla();

  printf("Saldo actual es %.2f\n", oldBalance);
  puts("¿Cuánto desea agregar?");
  while (1) {
    while (getchar() != '\n');
    if (scanf("%lf", &change)) break;
    if (scanf(" %c", &exit)) {
      if (exit == 'e') {
        limpiarPantalla();
        return oldBalance;
      }
    }
    printf("Lo siento, esa no es una cantidad válida, por favor intente de nuevo\n");
  }

  newBalance = oldBalance + change;
  limpiarPantalla();

  User* user = getUserByUsername(map, username);
  if (user != NULL) {
    user->balance = newBalance;
  }

  return newBalance;
}

void saveUser(double balance, char* username, HashMap* map) {
  User* user = getUserByUsername(map, username);
  if (user != NULL) {
    user->balance = balance;
  }

  saveUsers(map, "users.txt");
}

double bet(double balance, horse horses[H_NUM]) {
  while(1) {
    int selectedCarril = 0;
    double amountBet = 0;
    char exit;
    limpiarPantalla();
    printf("Saldo actual: $%.2f\n", balance);
    puts("Caballos que correrán en la próxima carrera:");
    printHorses(horses);
    puts("¿En qué carril desea apostar? (1-4)");
    while(1) {
      if(scanf("%d", &selectedCarril) == 1) {
        if (selectedCarril >= 1 && selectedCarril < H_NUM) {
          break;
        }
      }
      while (getchar() != '\n');
      printf("Lo siento, ese no es un carril válido, por favor intente de nuevo (1-4)\n");
    }

    puts("¿Cuánto desea apostar?");
    while(1) {
      if(scanf("%lf", &amountBet) == 1) {
        if(amountBet <= balance) {
            balance -= amountBet;
            horses[selectedCarril].amountBet += amountBet;
            limpiarPantalla();
            printf("$%.2f apostado al caballo %s en el carril %d.\n", amountBet, horses[selectedCarril].name, selectedCarril);
            break;
        }
        puts("Fondos insuficientes en la cuenta, por favor intente de nuevo.");
        continue;
      }
      while (getchar() != '\n');
      puts("Lo siento, esa no es una cantidad válida, por favor intente de nuevo.");
    }

    while(1) {
      puts("¿Desea apostar por otro caballo? S/N");
      scanf(" %c", &exit);
      if (exit == 'N' || exit == 'n') {
        limpiarPantalla();
        return balance;
      }
      if(exit == 'S' || exit == 's') break;
      printf("Lo siento, esa no es una respuesta válida, por favor intente de nuevo\n");
    }
  }
}

double watch(horse horses[H_NUM]) {
  char winner[100] = "";
  char exit;
  int i, j, move = 0, rnd = 0;
  double payout = 0.00;
  double winnings = 0.0;
  const int NAME_WIDTH = 20;
  const int TRACK_START = NAME_WIDTH + 1;  // +1 para el separador '|'

  // Reiniciar las distancias de los caballos
  for (i = 1; i < H_NUM; i++) {
    horses[i].distance = 0;
  }

  while (strlen(winner) == 0) {
    limpiarPantalla();

    // Mostrar información de los caballos en una línea
    for (i = 1; i < H_NUM; i++) {
      printf("%s: $%.2f (%i%%) ",horses[i].name,horses[i].amountBet,horses[i].winChance);
    }
    printf("\n\n");

    // Dibujar la pista
    for (i = 0; i < NAME_WIDTH; i++) printf(" ");
    for (i = 0; i < TRACK_LENGTH + 4; i++) printf("=");
    puts("");

    // Dibujar los caballos
    for (i = 1; i < H_NUM; i++) {
      switch(i) {
        case 1: REDC; break;
        case 2: GREEN; break;
        case 3: YELLOW; break;
        case 4: CYAN; break;
      }

      printf("%-*s|", NAME_WIDTH, horses[i].name);
      if (horses[i].distance < TRACK_LENGTH) {
        for (j = 0; j < horses[i].distance; j++) printf(" ");
        printf("*");
        for (j = 0; j < TRACK_LENGTH - horses[i].distance - 1; j++) printf(" ");
        printf("| |\n");
      } else {
        for (j = 0; j < TRACK_LENGTH - 1; j++) printf(" ");
        printf(" |*|\n");
        strncpy(winner, horses[i].name, sizeof(winner) - 1);
        winner[sizeof(winner) - 1] = '\0';
      }
      WHITE;
    }

    for (i = 0; i < NAME_WIDTH; i++) printf(" ");
    for (i = 0; i < TRACK_LENGTH + 4; i++) printf("=");
    puts("");

    if (strlen(winner) > 0) {
      for (i = 1; i < H_NUM; i++) {
        if (strcmp(winner, horses[i].name) == 0) {
          printf("¡El caballo %s gana! ", winner);
          if (horses[i].amountBet > 0) {
            payout = (horses[i].amountBet * (1.0 / (horses[i].winChance / 100.0)));
            printf("¡Ganaste $%.2f!\n", payout);
            winnings = payout;
          } else printf("\n");
          break;
        }
      }
    }

    if (rnd % 4 == 0) {
      move = (rand() % 100) + 1;
      int cumulativeChance = 0;
      for (i = 1; i < H_NUM; i++) {
        cumulativeChance += horses[i].winChance;
        if (move <= cumulativeChance) {
          horses[i].distance++;
          break;
        }
      }
    } else {
      move = (rand() % (H_NUM - 1)) + 1;
      horses[move].distance++;
    }

    rnd++;
    usleep(100000);
  }

  while (getchar() != '\n');
  puts("Presione cualquier tecla para regresar al menú:");
  scanf("%c", &exit);
  limpiarPantalla();
  return winnings;
}