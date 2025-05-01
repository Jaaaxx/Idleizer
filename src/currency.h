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

void addCurrencies(Core* core, const char** names, const VrVec* positions, int* parents, bool* hiddens, int count);
int addCurrency(Core* core, const char* name, const VrVec position, bool hidden, int parent);

#endif
