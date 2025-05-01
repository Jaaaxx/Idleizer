#include "game.h"
#include <stdbool.h>
#include <stddef.h>

Section *getSection(Core *core, int idx) {
  return idx >= 0 ? &core->sections[idx] : NULL;
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

