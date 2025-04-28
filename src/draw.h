#ifndef DRAW_H
#define DRAW_H

#include "button.h"
#include "currency.h"
#include "ticker.h"
#include "label.h"

void drawSectionOutlines(int game_width, int game_height);
void drawButton(const Button* button); 
void drawButtons(const Button* buttons, const int buttons_count);
void drawCurrencies(Currency* currencies, int currencies_count); 
void drawTicker(Ticker ticker, Color color);
void drawLabels(Label* labels, int labels_count);
#endif
