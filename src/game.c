#include "game.h"
#include <stdbool.h>

Currency* CURRENCIES = 0; 
int CURRENCIES_COUNT = 0; 

Button* BUTTONS = 0;
int BUTTONS_COUNT = 0;

Ticker* TICKERS = 0;
int TICKERS_COUNT = 0;

Label* LABELS = 0;
int LABELS_COUNT = 0;

void handleTickers(Ticker* tickers, int tickers_count) {
  bool tickerReached = false;
  for (int i = 0; i < TICKERS_COUNT; i++) {
    tickerReached = false;
    // Should move this somewhere else (not in draw)
    if (TICKERS[i].tick == TICKERS[i].frequency) {
      TICKERS[i].tick = 0;
      TICKERS[i].handler();
      tickerReached = true;
    }
    
    drawTicker(TICKERS[i], tickerReached ? RED : BLACK);
    TICKERS[i].tick++;
  }
}

void mouseButtonsHandler(Button* buttons, int buttons_count, int* mouseBtn) {
  for (int i = 0; i < buttons_count; i++) {
    if (CheckCollisionPointRec(GetMousePosition(), *buttons[i].rec)) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        buttons[i].handler();
        *mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *mouseBtn = -1;
      }
    }
  }
}

