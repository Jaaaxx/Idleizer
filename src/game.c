#include "game.h"
#include <stdbool.h>

int GAME_WIDTH = 0;
int GAME_HEIGHT = 0;

Core* GAME_CORE = 0;

Section* SECTIONS = 0;
int SECTIONS_COUNT = 0;

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
    if (TICKERS[i].tick == TICKERS[i].frequency) {
      TICKERS[i].tick = 0;
      TICKERS[i].handler(TICKERS[i].ctx);
      tickerReached = true;
      if (TICKERS[i].displayTick == 10) {
        TICKERS[i].displayTick = 0;
      }
      TICKERS[i].displayTick++;
    }
    
    if (!TICKERS[i].hidden) {
      drawTicker(TICKERS[i], BLACK);
    }
    TICKERS[i].tick++;
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

void setGameSize(int game_width, int game_height) {
  GAME_WIDTH = game_width;
  GAME_HEIGHT = game_height;
}
