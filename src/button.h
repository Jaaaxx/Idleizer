#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "vr_rec.h"
#include "section.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Core Core;

typedef struct {
  char* text;
  VrRec rec;
  void (*handler)(void*);
  void* ctx;
  int sec;
  bool hidden;
} Button;

int addButtons(Core* core, Button* buttons, int count); 
int addButton(Core* core, Button button); 

#endif
