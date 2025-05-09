#include "ticker.h"
#include "core.h"
#include <string.h>
#include "external/resource_loader.h"

static void setDefaultTicker(Ticker ticker, Ticker* ptr) {
  ptr->name = ticker.name ? ticker.name : "default_name";
  ptr->pos = ticker.pos;
  ptr->frequency = ticker.frequency > 0 ? ticker.frequency : 10;
  ptr->tick = ticker.tick;
  ptr->displayTick = ticker.displayTick;
  ptr->handler = ticker.handler ? ticker.handler : NULL;
  ptr->ctx = ticker.ctx ? ticker.ctx : NULL;
  ptr->sec = ticker.sec >= 0 ? ticker.sec : -1;
  ptr->hidden = ticker.hidden;
  ptr->font = ticker.font != NULL ? ticker.font : getDefaultFontResource();
  ptr->_font = ticker._font;
  ptr->fontSize = ticker.fontSize > 0 ? ticker.fontSize : 20;
}

int addTickers(Core* core, Ticker* tickers, int count) {
  if (core->tickers == NULL) {
    core->tickers_size = 0;
  }

  core->tickers = realloc(core->tickers, sizeof(Ticker) * (core->tickers_size + count));
  for (int i = 0; i < count; i++) {
    setDefaultTicker(tickers[i], &core->tickers[i+core->tickers_size]);
  }

  int index = core->tickers_size;
  core->tickers_size += count;
  return index;
}

int addTicker(Core* core, Ticker ticker) {
  if (core->tickers == NULL) {
    core->tickers_size = 0;
  }

  core->tickers = realloc(core->tickers, sizeof(Ticker) * (core->tickers_size + 1));
  setDefaultTicker(ticker, &core->tickers[core->tickers_size]);

  return core->tickers_size++;
}


void drawTicker(Core* core, Ticker* ticker, Color color) {
  LOAD_FONT(ticker);
  if (!ticker->hidden && !sectionHidden(core, ticker->sec)) {
    Vector2 vec = getTrueVec(core, ticker->pos, getSection(core, ticker->sec));
    
    char ticker_amount_text[256];
    
    strcpy(ticker_amount_text, ticker->name);
    int nameLen = strlen(ticker->name);
    
    for (int i = 0; i < ticker->displayTick; i++) {
      ticker_amount_text[nameLen+i] = '.';
    }
    ticker_amount_text[nameLen+ticker->displayTick] = '\0';
    
    DrawTextEx(ticker->_font, ticker_amount_text, (Vector2) {vec.x, vec.y}, ticker->fontSize, 0.0f, color);
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
    
    drawTicker(core, t, BLACK);
    t->tick++;
  }
}

void unloadTickerResources(Core* core) {
  for (int i = 0; i < core->tickers_size; i++) {
    Ticker* ticker = &core->tickers[i];
    UNLOAD_FONT(ticker);
  }
}

