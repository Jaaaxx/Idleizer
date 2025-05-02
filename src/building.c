#include "building.h"
#include <stddef.h>
#include <stdlib.h>

// Helper method for calculating vertically placed building rows
VrVec calcBuildingOffsetPos(int buildings_size, int startX, int startY, int yOffset) {
  VrVec ret = { startX, buildings_size * startY + yOffset };
  return ret; 
}

static void defBuildTicker(void* context) {
  Building* ctx = (Building*) context;
  Currency* currs = ctx->core->currencies;
  currs[ctx->gCurr].amount += ((double) ctx->bv->amount) * ctx->bv->cps / 10.0;
}

static void defBuildingUpdateLabels(Building* ctx) {
  Currency* currs = ctx->core->currencies;
  if (&(ctx->texts->amount) != NULL) {
    setTextBuffer(&(ctx->texts->amount), "%s: %d", ctx->name, ctx->bv->amount);
  }
  if (&(ctx->texts->cps) != NULL) {
    setTextBuffer(&(ctx->texts->cps), "Per Second: %.1f %s", ctx->bv->amount*ctx->bv->cps,
                  currs[ctx->gCurr].name);
  }
  if (&(ctx->texts->button) != NULL) {
    setTextBuffer(&(ctx->texts->button), "Buy %s\n Costs %.1f %s", ctx->name,ctx->bv->cost,
                  currs[ctx->bCurr].name);
  }
}

static void defBuildButton(void* context) {
  Building* ctx = (Building*) context;
  Currency* currs = ctx->core->currencies;
  if (currs[ctx->bCurr].amount >= ctx->bv->cost) {
    Core* core = ctx->core;
    currs[ctx->bCurr].amount -= ctx->bv->cost;
    ctx->bv->amount++;
    ctx->bv->cost *= 1.15;
    core->labels[ctx->labels->amountLabel].hidden = false;
    core->labels[ctx->labels->cpsLabel].hidden = false;
    core->tickers[ctx->tickers->mTicker].hidden = false;
    core->sections[ctx->displaySect].hidden = false;
    defBuildingUpdateLabels(ctx);
  }
}


int setupBuilding(Core* core, char* name, double cps, double cost, 
                          int bCurr, int gCurr, BuildingPositions bps, void* gameData) {
  BuildingVals* bv = malloc(sizeof(BuildingVals));
  bv->amount = 0;
  bv->cps = cps;
  bv->cost = cost;

  BuildingLabels* bl = malloc(sizeof(BuildingLabels));
  BuildingTickers* btickers = malloc(sizeof(BuildingTickers));
  BuildingButtons* bbuttons = malloc(sizeof(BuildingButtons));

  Building* ctx = malloc(sizeof(Building));
  ctx->core = core;
  ctx->name = name;
  ctx->bv = bv;
  ctx->bCurr = bCurr;
  ctx->gCurr = gCurr;
  ctx->labels = bl;
  ctx->tickers = btickers;
  ctx->buttons = bbuttons;
  ctx->data = gameData;
  
  Section* secs = core->sections;

  // Default Building Sections
  if (bps.section != NULL) {
    ctx->displaySect = addSection(core, (Section) { .rec = bps.section->pos,
                                                    .bg = GRAY,
                                                    .hidden = true,
                                                    .parent = bps.section->sec });
  }

  // Default Building Tickers
  if (bps.ticker != NULL) {
     ctx->tickers->mTicker = addTicker(core, (Ticker) { .name = name,
                                                        .pos = bps.ticker->pos,
                                                        .frequency = 6,
                                                        .handler = defBuildTicker,
                                                        .ctx = ctx,
                                                        .hidden = true,
                                                        .sec = bps.ticker->sec });
  }
  // Default Building Labels
  ctx->texts = malloc(sizeof(BuildingTexts));

  if (bps.amountLabel != NULL) {
    ctx->labels->amountLabel = addLabel(core, (Label) { .text = ctx->texts->amount.text,
                                                        .pos = bps.amountLabel->pos, 
                                                        .color = BLACK,
                                                        .hidden = true,
                                                        .sec = bps.amountLabel->sec });
  }

  if (bps.cpsLabel != NULL) {
    ctx->labels->cpsLabel = addLabel(core, (Label) { .text = ctx->texts->cps.text,
                                                     .pos = bps.cpsLabel->pos,
                                                     .color = BLACK,
                                                     .hidden = true,
                                                     .sec = bps.cpsLabel->sec });
  }
  // Default Building Buttons
  if (bps.button != NULL) {
    ctx->buttons->buyButton = addButton(core, (Button) { .text = ctx->texts->button.text,
                                                         .rec = bps.button->pos,
                                                         .handler = defBuildButton,
                                                         .ctx = ctx,
                                                         .sec = bps.button->sec });
  }
  
  defBuildingUpdateLabels(ctx);
  core->buildings = realloc(core->buildings, sizeof(Building) * (core->buildings_size + 1));

  return core->buildings_size++;
}

