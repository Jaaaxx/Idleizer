#ifndef DRAW_H
#define DRAW_H

#include "button.h"
#include "currency.h"
#include "ticker.h"
#include "label.h"
#include "section.h"
#include "vr_rec.h"
#include "vr_vec.h"

#define TRANSPARENT CLITERAL(Color){ 255, 255, 255, 0 }

void drawSection(Section* section);
void drawSections(Section* sections, int count);
void drawButton(const Button* button); 
void drawButtons(const Button* buttons, const int buttons_count);
void drawCurrencies(Currency* currencies, int currencies_count); 
void drawTicker(Ticker ticker, Color color);
void drawLabels(Label* labels, int labels_count);
#endif
