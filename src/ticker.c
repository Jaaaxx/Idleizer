#include "ticker.h"
#include "core.h"

void addTickers(Core* core, char** texts, VrVec* secs, int* frequencies, void (**handlers)(void *), 
                   void** ctxs, int* parents, bool* hiddens, int count) {
  if (&core->tickers == NULL) {
    core->tickers_size = 0;
  }
  Ticker* tickers = realloc(core->tickers, sizeof(Ticker) * (core->tickers_size + count));
  for (int i = 0; i < count; i++) {
    tickers[i+core->tickers_size].name = texts[i];
    tickers[i+core->tickers_size].pos = secs[i];
    tickers[i+core->tickers_size].frequency = frequencies[i];
    tickers[i+core->tickers_size].tick = 0;
    tickers[i+core->tickers_size].displayTick = 0;
    tickers[i+core->tickers_size].handler = handlers[i];
    tickers[i+core->tickers_size].ctx = ctxs[i];
    tickers[i+core->tickers_size].sec = parents[i];
    tickers[i+core->tickers_size].hidden = hiddens[i];
  }
  core->tickers = tickers;
  core->tickers_size += count;
}

int addTicker(Core* core, char* name, VrVec pos, int frequency, 
                void (*handler)(void*), void* ctx, bool hidden, int sec) {
  if (&core->tickers == NULL) {
    core->tickers_size = 0;
  }

  core->tickers = realloc(core->tickers, sizeof(Ticker) * (core->tickers_size + 1));
  
  Ticker* t = &core->tickers[core->tickers_size];
  t->name = name;
  t->pos = pos;
  t->frequency = frequency;
  t->tick = 0;
  t->displayTick = 0;
  t->handler = handler;
  t->ctx = ctx;
  t->sec = sec;
  t->hidden = hidden;

  return core->tickers_size++;
}
