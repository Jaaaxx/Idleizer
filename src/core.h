#ifndef CORE_H
#define CORE_H

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
} Core;

#endif
