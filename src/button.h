#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

typedef struct {
  Rectangle* rect;
  char* text;
  void (*func)();
} Button;

#endif
