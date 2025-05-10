#include "currency.h"
#include "core.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"
#include "external/resource_loader.h"

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
  ptr->cpsMult = currency.cpsMult != 0 ? currency.cpsMult : 1;
  
  // Default initialization for _button field to prevent issues with uninitialized values
  ptr->_button = -1;
  
  // Copy button properties
  ptr->button = currency.button;
  ptr->button.text = currency.button.text != NULL ? currency.button.text : ptr->name;
  
  // Ensure button rectangle has valid values
  if (currency.button.rec.x == 0 && currency.button.rec.y == 0 &&
      currency.button.rec.w == 0 && currency.button.rec.h == 0) {
    ptr->button.rec = (VrRec) { ptr->pos.x, ptr->pos.y + 20, 30, 10 };
  } else {
    ptr->button.rec = currency.button.rec;
  }
  
  ptr->sec = currency.sec != 0 ? currency.sec : -1;
  ptr->button.sec = currency.button.sec > 0 ? currency.button.sec : ptr->sec;
  ptr->hidden = currency.hidden;
  ptr->perClick = currency.perClick > 0 ? currency.perClick : 1;
  ptr->amountLabel = currency.amountLabel;
  ptr->amountLabel.color = currency.amountLabel.color.r != 0 || currency.amountLabel.color.g != 0 ||
                        currency.amountLabel.color.b != 0 ? currency.amountLabel.color : BLACK;
  ptr->amountLabel.font = currency.amountLabel.font != NULL ? currency.amountLabel.font 
                                                            : getDefaultFontResource();
  ptr->amountLabel.fontSize = currency.amountLabel.fontSize != 0 ? currency.amountLabel.fontSize
                                                                 : 20;
  ptr->amountLabel.pos = currency.amountLabel.pos.x != 0 || currency.amountLabel.pos.y != 0 ?
                                                          currency.amountLabel.pos :
                                                          (VrRec) {ptr->pos.x, ptr->pos.y};
  ptr->amountLabel.sec = currency.amountLabel.sec != 0 ? currency.amountLabel.sec : ptr->sec;
  ptr->cpsLabel = currency.cpsLabel;
  ptr->cpsLabel.color = currency.cpsLabel.color.r != 0 || currency.cpsLabel.color.g != 0 ||
                        currency.cpsLabel.color.b != 0 ? currency.cpsLabel.color : BLACK;
  ptr->cpsLabel.font = currency.cpsLabel.font != NULL ? currency.cpsLabel.font 
                                                      : getDefaultFontResource();
  ptr->cpsLabel.fontSize = currency.cpsLabel.fontSize != 0 ? currency.cpsLabel.fontSize
                                                           : 20;
  ptr->cpsLabel.pos= currency.cpsLabel.pos.x != 0 || currency.cpsLabel.pos.y != 0 ?
                                                          currency.cpsLabel.pos:
                                                          (VrRec) {ptr->pos.x, ptr->pos.y+3};
  ptr->cpsLabel.sec = currency.cpsLabel.sec != 0 ? currency.cpsLabel.sec : ptr->sec;
}

static void addCurrButton(Core* core, int idx) {
  Currency* curr = &core->currencies[idx];

  if (curr->button.ctx == NULL) {
    CurrClickCtx* ctx = (CurrClickCtx*) malloc(sizeof(CurrClickCtx));

    ctx->core = core;
    ctx->currency = idx;

    curr->button.ctx = ctx;
    curr->button.handler = defClickHandler;
    // Track this context for memory management
    track_curr_context(ctx);
  }

  if (curr->button.rec.x == 0 && curr->button.rec.y == 0 && 
      curr->button.rec.w == 0 && curr->button.rec.h == 0) {
    curr->button.rec = (VrRec) { curr->pos.x, curr->pos.y + 20, 30, 10 };
  }

  curr->_button = addButton(core, curr->button);
  curr->button = (Button) {0};
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
  LOAD_FONT(&c->amountLabel);
  LOAD_FONT(&c->cpsLabel);

  if (!c->hidden && !sectionHidden(core, c->sec)) {
    Rectangle amountRec = getTrueRec(core, c->amountLabel.pos, getSection(core, c->amountLabel.sec));
    Rectangle cpsRec = getTrueRec(core, c->cpsLabel.pos, getSection(core, c->cpsLabel.sec));

    char currency_amount_text[256];
    char currency_cps_text[64];

    sprintf(currency_amount_text, "%s: %.0f", c->name, c->amount);
    sprintf(currency_cps_text, "CPS: %.2f", c->cps);
    
    DrawTextEx(c->amountLabel._font, currency_amount_text, (Vector2) {amountRec.x, amountRec.y}, 
               c->amountLabel.fontSize, 0.0f, c->amountLabel.color);
    DrawTextEx(c->cpsLabel._font, currency_cps_text, (Vector2) {cpsRec.x, cpsRec.y}, 
               c->cpsLabel.fontSize, 0.0f, c->cpsLabel.color);
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

void unloadCurrencyResources(Core* core) {
  for (int i = 0; i < core->currencies_size; i++) {
    Currency* currency = &core->currencies[i];
    UNLOAD_FONT(&currency->amountLabel);
    UNLOAD_FONT(&currency->cpsLabel);
  }
}

