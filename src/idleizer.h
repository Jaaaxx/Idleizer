#ifndef IDLEIZER_H
#define IDLEIZER_H

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

#include "currency.h"
#include "button.h"
#include "game.h"
#include "draw.h"
#include "ticker.h"
#include "section.h"
#include "core.h"

typedef struct {
  char text[64];
} TextBuffer;

void runGame(Core* core, int game_width, int game_height, char* title);

void destroyCore(Core* core);
void setTextBuffer(TextBuffer* buffer, const char* fmt, ...);
void createSections(Core* core, const VrRec* rects, const Color* colors,
                    const int* parent_indices, int count);
void createCurrencies(Core* core, const char** names, const VrVec* positions, 
                      Section** parents, int count);
void createButtons(Core* core, const char** texts, const VrRec* recs,
                   void (**handlers)(void *), void** ctxs, Section** secs, int count);
void createLabels(Core* core, char** texts, VrVec* vecs, Color* colors,
                  bool* hiddens, Section** parents, int count);
void createTickers(Core* core, char** texts, VrVec* secs, int* frequencies, void (**handlers)(void *), 
                   void** ctxs, Section** parents, bool* hiddens, int count);

int addSection(Core* core, const VrRec rect, const Color color, const Section* parent);

int addCurrency(Core* core, const char* name, const VrVec position, Section* parent);

int addTicker(Core* core, char* name, VrVec pos, int frequency,
                  void (*handler)(void*), void* ctx, bool hidden, Section* sec);

int addLabel(Core* core, char* text, VrVec pos, Color color,
                bool hidden, Section* parent);

int addButton(Core* core, char* text, VrRec rec,
                  void (*handler)(void*), void* ctx, Section* sec);
#endif
