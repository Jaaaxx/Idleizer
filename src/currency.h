#ifndef CURRENCY_H
#define CURRENCY_H
#include "raylib.h"
#include "vr_vec.h"
#include "section.h"

typedef struct {
  char* name;
  double amount;
  VrVec pos;
  Section* sec;
} Currency;

#endif
