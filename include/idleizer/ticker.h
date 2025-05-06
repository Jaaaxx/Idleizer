#ifndef TICKER_H
#define TICKER_H
#include "vr_vec.h"
#include <stdbool.h>

#include <stdlib.h>

typedef struct Core Core;

typedef struct {
  char* name;
  VrVec pos;
  int frequency;
  int tick;
   // used for visual display purposes, extends tick
  int displayTick;
  void (*handler)(); 
  void* ctx;
  int sec;
  bool hidden;
  char* font;
  Font _font;
  int fontSize;
} Ticker;

int addTickers(Core* core, Ticker* tickers, int count); 
int addTicker(Core* core, Ticker ticker);
void drawTicker(Core* core, Ticker* ticker, Color color);
void handleTickers(Core* core);
#endif
