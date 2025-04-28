#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "raylib.h"
#include "currency.h"
#include "ticker.h"
#include "draw.h"
#include "label.h"

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
#endif
