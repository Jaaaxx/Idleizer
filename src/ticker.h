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
} Ticker;
void addTickers(Core* core, char** texts, VrVec* secs, int* frequencies, void (**handlers)(void*), void** ctxs, int* parents, bool* hiddens, int count);
int addTicker(Core* core, char* name, VrVec pos, int frequency, void (*handler)(void*), void* ctx, bool hidden, int sec);
#endif
