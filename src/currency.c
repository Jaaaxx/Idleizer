#include "currency.h"
#include "core.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct CurrClickCtx {
  Core* core;
  int currency;
} CurrClickCtx;

// Array to keep track of currency button contexts
static CurrClickCtx** curr_contexts = NULL;
static int curr_contexts_size = 0;

// Function to add a context to our tracking array
static void track_curr_context(CurrClickCtx* ctx) {
  curr_contexts = realloc(curr_contexts, sizeof(CurrClickCtx*) * (curr_contexts_size + 1));
  curr_contexts[curr_contexts_size++] = ctx;
}

// Function to free all tracked currency contexts
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
  VrRec buttonPos = { pos.x, pos.y + 20, 20, 10 };

  addButton(core, (Button) { .text = curr.name,
                             .rec = buttonPos,
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

