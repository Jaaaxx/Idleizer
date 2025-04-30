#ifndef TICKER_H
#define TICKER_H
#include "vr_vec.h"
#include <stdbool.h>

typedef struct {
  char* name;
  VrVec pos;
  int frequency;
  int tick;
   // used for visual display purposes, extends tick
  int displayTick;
  void (*handler)(); 
  void* ctx;
  Section* sec;
  bool hidden;
} Ticker;
#endif
