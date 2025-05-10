#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "vr_rec.h"
#include "section.h"
#include "label.h"
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
  Image image;
  Texture _texture;
  Label label;
} Button;

void drawButtons(Core* core);
int addButtons(Core* core, Button* buttons, int count); 
int addButton(Core* core, Button button);
void unloadButtonResources(Core* core);

#endif
