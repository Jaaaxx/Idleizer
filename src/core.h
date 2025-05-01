#ifndef CORE_H
#define CORE_H
#include "section.h"
#include "currency.h"
#include "button.h"
#include "label.h"
#include "ticker.h"

typedef struct Core {
  Section* sections;
  int sections_size;
  Currency* currencies;
  int currencies_size;
  Button* buttons;
  int buttons_size;
  Label* labels;
  int labels_size;
  Ticker* tickers;
  int tickers_size;

  int buildings_size;
} Core;

#endif
