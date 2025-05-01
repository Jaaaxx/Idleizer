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
#include <stdbool.h>

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

// Core loop and lifecycle
void runGame(Core* core, int game_width, int game_height, char* title);
void destroyCore(Core* core);

// Utility
void setTextBuffer(TextBuffer* buffer, const char* fmt, ...);

// Section management
void createSections(Core* core, const VrRec* rects, const Color* colors, const int* parent_indices, const bool* hiddens, int count);
int addSection(Core* core, const VrRec rect, const Color color, const bool hidden, int parent);

// Currency management
void createCurrencies(Core* core, const char** names, const VrVec* positions, int* parents, bool* hiddens, int count);
int addCurrency(Core* core, const char* name, const VrVec position, bool hidden, int parent);

// Button management
void createButtons(Core* core, const char** texts, const VrRec* recs, void (**handlers)(void*), void** ctxs, int* secs, bool* hiddens, int count);
int addButton(Core* core, char* text, VrRec rec, void (*handler)(void*), void* ctx, bool hidden, int sec);

// Label management
void createLabels(Core* core, char** texts, VrVec* vecs, Color* colors, bool* hiddens, int* parents, int count);
int addLabel(Core* core, char* text, VrVec pos, Color color, bool hidden, int parent);

// Ticker management
void createTickers(Core* core, char** texts, VrVec* secs, int* frequencies, void (**handlers)(void*), void** ctxs, int* parents, bool* hiddens, int count);
int addTicker(Core* core, char* name, VrVec pos, int frequency, void (*handler)(void*), void* ctx, bool hidden, int sec);
#endif
