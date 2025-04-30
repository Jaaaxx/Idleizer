#include "game.h"
#include <stdbool.h>

void handleTickers(Ticker* tickers, int tickers_count) {
  bool tickerReached = false;
  for (int i = 0; i < tickers_count; i++) {
    tickerReached = false;
    if (tickers[i].tick == tickers[i].frequency) {
      tickers[i].tick = 0;
      tickers[i].handler(tickers[i].ctx);
      tickerReached = true;
      if (tickers[i].displayTick == 10) {
        tickers[i].displayTick = 0;
      }
      tickers[i].displayTick++;
    }
    
    if (!tickers[i].hidden) {
      drawTicker(tickers[i], BLACK);
    }
    tickers[i].tick++;
  }
}

void mouseButtonsHandler(Button* buttons, int buttons_count, int* mouseBtn) {
  for (int i = 0; i < buttons_count; i++) {
    if (CheckCollisionPointRec(GetMousePosition(), *getTrueRec(buttons[i].rec, buttons[i].sec))) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        buttons[i].handler(buttons[i].ctx);
        *mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *mouseBtn = -1;
      }
    }
  }
}

