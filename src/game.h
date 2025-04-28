#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "raylib.h"
#include "currency.h"

extern Currency* CURRENCIES;
extern int CURRENCIES_COUNT;
extern Button* BUTTONS;
extern int BUTTONS_COUNT;

void setupCurrencies(Currency* currencies, int count);
void setupButtons(Button* buttons, int count);
#endif
