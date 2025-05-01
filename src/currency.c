#include "currency.h"
#include "core.h"

typedef struct CurrClickCtx {
  Core* core;
  int currency;
} CurrClickCtx;

static void defClickHandler(void* context) {
  CurrClickCtx* ctx = (CurrClickCtx*) context;
  Currency* curr= &(ctx->core->currencies[ctx->currency]);
  curr->amount += curr->perClick;
}

void addCurrencies(Core* core, const char** names, const VrVec* positions, int* parents, bool* hiddens, int count) {
  if (&core->currencies == NULL) {
    core->currencies_size = 0;
  }
  Currency* currencies = realloc(core->currencies, sizeof(Currency) * (core->currencies_size + count));
  for (int i = 0; i < count; i++) {
    currencies[i+core->currencies_size].name = names[i];
    currencies[i+core->currencies_size].amount = 0.0;
    currencies[i+core->currencies_size].pos = positions[i];
    currencies[i+core->currencies_size].sec = parents[i];
    currencies[i+core->currencies_size].hidden = hiddens[i];
    currencies[i+core->currencies_size].perClick = 1;

    VrVec pos = positions[i];
    VrRec buttonPos = { pos.x, pos.y + 20, 20, 10 };
    CurrClickCtx* ctx = malloc(sizeof(CurrClickCtx));
    ctx->core = core;
    ctx->currency = i;

    addButton(core, names[i], buttonPos, defClickHandler, ctx, false, parents[i]);
  }
  
  core->currencies = currencies;
  core->currencies_size += count;
}

int addCurrency(Core* core, const char* name, const VrVec position, bool hidden, int parent) {
  if (&core->currencies == NULL) {
    core->currencies_size = 0;
  }
  core->currencies = realloc(core->currencies, sizeof(Currency) * (core->currencies_size + 1));

  Currency* c = &core->currencies[core->currencies_size];
  c->name = name;
  c->amount = 0.0;
  c->pos = position;
  c->sec = parent;
  c->hidden = hidden;
  c->perClick = 1;

  VrRec buttonPos = { position.x, position.y + 20, 20, 10 };
  CurrClickCtx* ctx = malloc(sizeof(CurrClickCtx));
  ctx->core = core;
  ctx->currency = core->currencies_size + 1;

  addButton(core, name, buttonPos, defClickHandler, ctx, false, parent);

  return core->currencies_size++;
}

