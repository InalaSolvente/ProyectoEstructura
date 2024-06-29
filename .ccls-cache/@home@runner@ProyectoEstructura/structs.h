#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct horse
{
  char name[100];
  int winChance;
  double amountBet;
  int distance;
} horse;

#endif