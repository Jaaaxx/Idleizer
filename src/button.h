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

void addButtons(Core* core, const char** texts, const VrRec* recs, void (**handlers)(void*), void** ctxs, int* secs, bool* hiddens, int count);
int addButton(Core* core, char* text, VrRec rec, void (*handler)(void*), void* ctx, bool hidden, int sec);

#endif
