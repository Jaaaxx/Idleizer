#ifndef CURRENCY_H
#define CURRENCY_H
#include "raylib.h"
#include "vr_vec.h"
#include "section.h"
#include "button.h"
#include "label.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Core Core;

typedef struct {
  char* name;
  double amount;
  VrVec pos;
  Button button;
  int _button;
  int sec;
  bool hidden;
  double cps;
  double perClick;
  Label amountLabel;
  Label cpsLabel;
} Currency;

int addCurrencies(Core* core, Currency* currencies, int count); 
int addCurrency(Core* core, Currency currency);
void freeCurrencyContexts();
void drawCurrency(Core* core, Currency* c);
void drawCurrencies(Core* core);
void handleCurrencies(Core* core);
void unloadCurrencyResources(Core* core);

#endif
