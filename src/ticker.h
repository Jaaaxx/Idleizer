#ifndef TICKER_H
#define TICKER_H
#include "vr_rec.h"

typedef struct {
  char* name;
  int frequency;
  int tick;
  VrRec pos;
  void (*handler)(); 
  Section* sec;
} Ticker;
#endif
