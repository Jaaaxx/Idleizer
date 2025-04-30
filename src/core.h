#ifndef CORE_H
#define CORE_H

typedef struct Core {
  Section* sections;
  Currency* currencies;
  Button* buttons;
  Label* labels;
  Ticker* tickers;
} Core;

#endif
