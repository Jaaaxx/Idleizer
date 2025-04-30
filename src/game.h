#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "raylib.h"
#include "currency.h"
#include "ticker.h"
#include "draw.h"
#include "label.h"
#include "core.h"

extern int GAME_WIDTH;
extern int GAME_HEIGHT;
extern Core* GAME_CORE;
extern Section* SECTIONS;
extern int SECTIONS_COUNT;
extern Currency* CURRENCIES;
extern int CURRENCIES_COUNT;
extern Button* BUTTONS;
extern int BUTTONS_COUNT;
extern Ticker* TICKERS;
extern int TICKERS_COUNT;
extern Label* LABELS;
extern int LABELS_COUNT;

void handleTickers();
void mouseButtonsHandler(Button* buttons, int buttons_count, int* mouseBtn);
void setGameSize(int game_width, int game_height);
#endif
