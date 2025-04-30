#ifndef TICKER_H
#define TICKER_H
#include "vr_rec.h"
#include <stdbool.h>

typedef struct {
  char* name;
  int frequency;
  int tick;
   // used for visual display purposes, extends tick
  int displayTick;
  VrRec pos;
  void (*handler)(); 
  void* ctx;
  Section* sec;
  bool hidden;
} Ticker;
#endif
