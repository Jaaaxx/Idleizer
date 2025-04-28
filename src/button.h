#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

typedef struct {
  Rectangle* rec;
  char* text;
  void (*handler)();
} Button;

#endif
