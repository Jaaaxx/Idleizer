#include "draw.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "core.h"
#include "game.h"

bool ColorsEqual(Color c1, Color c2) {
    return (c1.r == c2.r) &&
           (c1.g == c2.g) &&
           (c1.b == c2.b) &&
           (c1.a == c2.a);
}

void drawSections(Core* core) {
  for (int i = 0; i < core->sections_size; i++) {
    const Section* s = &core->sections[i];
    if (!s->hidden) {
      Rectangle rec = getSectionRec(core, s);  
      DrawRectangleRec(rec, s->bg); 
      DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, BLACK);
    }
  }
}

void drawButtons(Core* core) {
  for (int i = 0; i < core->buttons_size; i++) {
    const Button* b = &core->buttons[i];
    if (!b->hidden) {
      Rectangle rec = getTrueRec(core, b->rec, getSection(core, b->sec));  
      DrawRectangleRec(rec, Fade(LIGHTGRAY, 0.3f));
      DrawRectangleRoundedLinesEx(rec, 0.0f, 0.0f, 1.0f, Fade(BLACK, 0.4f));
      DrawText(b->text, rec.x + 5, rec.y, 20, RED);
    }
  }
}

void drawCurrency(Core* core, Currency* c) {
  if (!c->hidden) {
    Vector2 rec = getTrueVec(core, c->pos, getSection(core, c->sec));

    char currency_amount_text[256];
    char currency_cps_text[64];
    
    sprintf(currency_amount_text, "%s: %.0f", c->name, c->amount);
    sprintf(currency_cps_text, "CPS: %.2f", c->cps);
    
    DrawText(currency_amount_text, rec.x, rec.y, 20, RED);
    DrawText(currency_cps_text, rec.x, rec.y + 25, 20, RED);
  }
}

void drawCurrencies(Core* core) {
  for (int i = 0; i < core->currencies_size; i++) {
    const Currency* c = &core->currencies[i];
    if (!c->hidden) {
      drawCurrency(core, c);
    }
  }
}

void drawTicker(Core* core, Ticker* ticker, Color color) {
  Vector2 vec = getTrueVec(core, ticker->pos, getSection(core, ticker->sec));
  
  char ticker_amount_text[256];
  
  strcpy(ticker_amount_text, ticker->name);
  int nameLen = strlen(ticker->name);
  
  for (int i = 0; i < ticker->displayTick; i++) {
    ticker_amount_text[nameLen+i] = '.';
  }
  ticker_amount_text[nameLen+ticker->displayTick] = '\0';
  
  DrawText(ticker_amount_text, vec.x, vec.y, 20, color);
}

void drawLabels(Core* core) {
  for (int i = 0; i < core->labels_size; i++) {
    const Label* l = &core->labels[i];
    if (!l->hidden) {
      Vector2 vec = getTrueVec(core, l->pos, getSection(core, l->sec));
      DrawText(l->text, vec.x, vec.y, l->fontSize, l->color);
    }
  }
}
