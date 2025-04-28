#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "vr_rec.h"
#include "section.h"

typedef struct {
  VrRec rec;
  char* text;
  void (*handler)();
  Section* sec;
} Button;

#endif
