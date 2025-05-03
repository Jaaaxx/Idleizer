#include "currency.h"
#include "core.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"

typedef struct CurrClickCtx {
  Core* core;
  int currency;
} CurrClickCtx;

static CurrClickCtx** curr_contexts = NULL;
static int curr_contexts_size = 0;

static void track_curr_context(CurrClickCtx* ctx) {
  curr_contexts = realloc(curr_contexts, sizeof(CurrClickCtx*) * (curr_contexts_size + 1));
  curr_contexts[curr_contexts_size++] = ctx;
}

void freeCurrencyContexts() {
  if (curr_contexts) {
    for (int i = 0; i < curr_contexts_size; i++) {
      if (curr_contexts[i]) {
        free(curr_contexts[i]);
      }
    }
    free(curr_contexts);
    curr_contexts = NULL;
    curr_contexts_size = 0;
  }
}

static void defClickHandler(void* context) {
  CurrClickCtx* ctx = (CurrClickCtx*) context;
  Currency* curr= &(ctx->core->currencies[ctx->currency]);
  curr->amount += curr->perClick;
}

static void setDefaultCurrency(Currency currency, Currency* ptr) {
  ptr->name = currency.name ? currency.name : "default_name";
  ptr->amount = currency.amount;
  ptr->pos = currency.pos;
  ptr->buttonRec = currency.buttonRec.x != 0 || currency.buttonRec.y != 0 ||
                   currency.buttonRec.w != 0 || currency.buttonRec.h != 0 ? currency.buttonRec :
                                                                    (VrRec) { ptr->pos.x,
                                                                              ptr->pos.y + 20,
                                                                              30, 10 };
  ptr->sec = currency.sec >= 0 ? currency.sec : -1;
  ptr->hidden = currency.hidden;
  ptr->perClick = currency.perClick > 0 ? currency.perClick : 1;
}

static void addCurrButton(Core* core, int idx) {
  CurrClickCtx* ctx = malloc(sizeof(CurrClickCtx));
  ctx->core = core;
  ctx->currency = idx;
  
  // Track this context
  track_curr_context(ctx);

  Currency curr = core->currencies[idx];
  VrVec pos = curr.pos;

  addButton(core, (Button) { .text = curr.name,
                             .rec = curr.buttonRec,
                             .handler = defClickHandler,
                             .ctx = ctx,
                             .sec = curr.sec });
}

int addCurrencies(Core* core, Currency* currencies, int count) {
  if (core->currencies == NULL) {
    core->currencies_size = 0;
  }

  core->currencies = realloc(core->currencies, sizeof(Currency) * (core->currencies_size + count));
  for (int i = 0; i < count; i++) {
    setDefaultCurrency(currencies[i], &core->currencies[i+core->currencies_size]);
    addCurrButton(core, i+core->currencies_size);
   }
 
  int index = core->currencies_size;
  core->currencies_size += count;
  return index;
}

int addCurrency(Core* core, Currency currency) {
  if (core->currencies == NULL) {
    core->currencies_size = 0;
  }

  core->currencies = realloc(core->currencies, sizeof(Currency) * (core->currencies_size + 1));
  setDefaultCurrency(currency, &core->currencies[core->currencies_size]);
  addCurrButton(core, core->currencies_size);

  return core->currencies_size++;
}

void drawCurrency(Core* core, Currency* c) {
  if (!c->hidden && !sectionHidden(core, c->sec)) {
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
    drawCurrency(core, &core->currencies[i]);
  }
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

