#ifndef CURRENCY_H
#define CURRENCY_H
#include "raylib.h"
#include "vr_vec.h"
#include "section.h"
#include <stdbool.h>

#include <stdlib.h>

typedef struct Core Core;

typedef struct {
  char* name;
  double amount;
  VrVec pos;
  int sec;
  bool hidden;
  double cps;
  double perClick;
} Currency;

int addCurrencies(Core* core, Currency* currencies, int count); 
int addCurrency(Core* core, Currency currency); 

#endif
