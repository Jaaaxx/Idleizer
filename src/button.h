#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "vr_rec.h"
#include "section.h"
#include <stdbool.h>

typedef struct {
  char* text;
  VrRec rec;
  void (*handler)(void*);
  void* ctx;
  int sec;
  bool hidden;
} Button;

#endif
