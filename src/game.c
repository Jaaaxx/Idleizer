#include "game.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

Section *getSection(Core *core, int idx) {
  return idx >= 0 ? &core->sections[idx] : NULL;
}

double calculateCPS(Core* core, int idx) {
  static int currSize = -1;
  static double* prevCurrs = NULL;

  if (currSize != core->currencies_size) {
    currSize = core->currencies_size;
    if (prevCurrs == NULL) {
      prevCurrs = (double*) calloc(core->currencies_size, sizeof(double));
    } else {
      prevCurrs = (double*) realloc(prevCurrs, core->currencies_size * sizeof(double));
    }
  }
  
  int amt = core->currencies[idx].amount;
  double ret;
  if (amt >= prevCurrs[idx]) {
    ret = (core->currencies[idx].amount - prevCurrs[idx]);
  } else {
    ret = core->currencies[idx].cps;
  }
  prevCurrs[idx] = core->currencies[idx].amount;
  return ret; 
}

void handleCurrencies(Core* core) {
  static int tick = 0;
  for (int i = 0; i < core->currencies_size; i++) {
    Currency* c = &core->currencies[i];
    if (tick++ == 60) {
      c->cps = calculateCPS(core, i);
      tick = 0;
    }
    drawCurrency(core, c);
  }
}

void handleTickers(Core* core) {
  bool tickerReached = false;
  for (int i = 0; i < core->tickers_size; i++) {
    Ticker* t = &core->tickers[i];
    tickerReached = false;
    if (t->tick == t->frequency) {
      t->tick = 0;
      t->handler(t->ctx);
      tickerReached = true;
      if (t->displayTick == 10) {
        t->displayTick = 0;
      }
      t->displayTick++;
    }
    
    if (!t->hidden) {
      drawTicker(core, t, BLACK);
    }
    t->tick++;
  }
}

void mouseButtonsHandler(Core* core, int* mouseBtn) {
  for (int i = 0; i < core->buttons_size; i++) {
    Button* b = &core->buttons[i];
    if (CheckCollisionPointRec(GetMousePosition(), *getTrueRec(core, b->rec, getSection(core, b->sec)))) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        b->handler(b->ctx);
        *mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *mouseBtn = -1;
      }
    }
  }
}

