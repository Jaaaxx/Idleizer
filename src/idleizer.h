#ifndef IDLEIZER_H
#define IDLEIZER_H

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "currency.h"
#include "button.h"
#include "game.h"
#include "draw.h"
#include "ticker.h"
#include "section.h"

typedef struct Core {
  Section* sections;
  Currency* currencies;
  Button* buttons;
  Label* labels;
  Ticker* tickers;
} Core;


typedef struct {
  char text[64];
} TextBuffer;

void runGame(int game_width, int game_height, char* title);

void setupCurrencies(Currency* currencies, int count);
void setupButtons(Button* buttons, int count);
void setupTickers(Ticker* tickers, int count);
void setupLabels(Label* labels, int count);
void setupSections(Section* sections, int count);
void destroyCore(Core* core);
void setTextBuffer(TextBuffer* buffer, const char* fmt, ...);
#endif
