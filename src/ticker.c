#include "ticker.h"
#include "core.h"

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

