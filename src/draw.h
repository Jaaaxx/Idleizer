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

void drawSections(Core* core);
void drawButtons(Core* core);
void drawCurrencies(Core* core);
void drawTicker(Core* core, Ticker* ticker, Color color);
void drawLabels(Core* core);
#endif
