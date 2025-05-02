#include "building.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct BuildingCtx {
  int idx;
  Core* core;
} BuildingCtx;


// Helper method for calculating vertically placed building rows
VrVec calcBuildingOffsetPos(int buildings_size, int startX, int startY, int yOffset) {
  VrVec ret = { startX, buildings_size * startY + yOffset };
  return ret; 
}

static void freeBuilding(Building* b) {
  if (b->texts.amount) {
    free(b->texts.amount);
  }
  if (b->texts.cps) {
    free(b->texts.cps);
  }
  if (b->texts.button) {
    free(b->texts.button);
  }
  if (b->internal) {
    free(b->internal);
  }
}

void freeAllBuildings(Core* core) {
  for (int i = 0; i < core->buildings_size; ++i) {
    freeBuilding(&core->buildings[i]);
  }
  free(core->buildings);
  core->buildings = NULL;
  core->buildings_size = 0;
}


static void defBuildTicker(void* context) {
  BuildingCtx* ctx = (BuildingCtx*) context;
  Building* b = &(ctx->core->buildings[ctx->idx]);
  Currency* currs = ctx->core->currencies;
  currs[b->gCurr].amount += ((double) b->vals.amount) * b->vals.cps / 10.0;
}

static void defBuildingUpdateLabels(Building* ctx) {
  Currency* currs = ctx->core->currencies;
  setTextBuffer(ctx->texts.amount, "%s: %d", ctx->name, ctx->vals.amount);
  setTextBuffer(ctx->texts.cps, "Per Second: %.1f %s", ctx->vals.amount*ctx->vals.cps,
                currs[ctx->gCurr].name);
  setTextBuffer(ctx->texts.button, "Buy %s\n Costs %.1f %s", ctx->name,ctx->vals.cost,
                currs[ctx->bCurr].name); 
}

static void defBuildButton(void* context) {
  BuildingCtx* ctx = (BuildingCtx*) context;
  Core* core = ctx->core;
  Building* b = &(core->buildings[ctx->idx]);
  Currency* currs = core->currencies;
  if (currs[b->bCurr].amount >= b->vals.cost) {
    currs[b->bCurr].amount -= b->vals.cost;
    b->vals.amount++;
    b->vals.cost *= 1.15;
    core->labels[b->labels.amountLabel].hidden = false;
    core->labels[b->labels.cpsLabel].hidden = false;
    core->tickers[b->tickers.mTicker].hidden = false;
    core->sections[b->displaySect].hidden = false;
    defBuildingUpdateLabels(b);
  }
}

static void setDefaultBuilding(Building building, Building* ptr) {
  ptr->core = building.core;
  ptr->name = building.name ? building.name : "default_name";
  ptr->vals = building.vals;
  ptr->bCurr = building.bCurr;
  ptr->gCurr = building.gCurr;
  ptr->labels = building.labels;
  ptr->tickers = building.tickers;
  ptr->texts = building.texts;
  ptr->texts.amount = malloc(sizeof(TextBuffer));
  ptr->texts.cps = malloc(sizeof(TextBuffer));
  ptr->texts.button = malloc(sizeof(TextBuffer));
  ptr->buttons = building.buttons;
  ptr->positions = building.positions;
  ptr->displaySect = building.displaySect;
  ptr->data = building.data;
}

Building newBuilding(Core* core) {
  BuildingVals vals = {0};

  BuildingLabels labels = {0};
  BuildingTickers tickers = {0};
  BuildingTexts texts = {0};
  BuildingButtons buttons = {0};
  BuildingPositions positions = {
    .ticker = { {0}, -2 },
    .amountLabel = { {0}, -2},
    .cpsLabel = { {0}, -2},
    .button = { {0}, -2},
    .section = { {0}, -2}
  };

  Building building = {
    .core = core,
    .vals = vals,
    .labels = labels,
    .texts = texts,
    .tickers = tickers,
    .buttons = buttons,
    .positions = positions,
    .displaySect = -1,
  };

  return building;
}


int addBuilding(Core* core, Building building) {
  if (core->buildings == NULL) {
    core->buildings_size = 0;
  }

  core->buildings = realloc(core->buildings, sizeof(Building) * (core->buildings_size + 1));
  Building* bld = &core->buildings[core->buildings_size];
  BuildingPositions bps = building.positions;
  
  setDefaultBuilding(building, bld);
  bld->core = core;

  BuildingCtx* ctx = malloc(sizeof(BuildingCtx));
  bld->internal = ctx;
  ctx->core = core;
  ctx->idx = core->buildings_size;
  
  // Default Building Sections
  if (bps.section.sec != -2) {
    bld->displaySect = addSection(core, (Section) { .rec = bps.section.pos,
                                                    .bg = GRAY,
                                                    .hidden = true,
                                                    .parent = bps.section.sec });
  }

  // Default Building Tickers
  if (bps.ticker.sec != -2) {
     bld->tickers.mTicker = addTicker(core, (Ticker) { .name = bld->name,
                                                       .pos = bps.ticker.pos,
                                                       .frequency = 6,
                                                       .handler = defBuildTicker,
                                                       .ctx = ctx,
                                                       .hidden = true,
                                                       .sec = bps.ticker.sec });
  }

  if (bps.amountLabel.sec != -2) {
    bld->labels.amountLabel = addLabel(core, (Label) { .text = bld->texts.amount->text,
                                                       .pos = bps.amountLabel.pos, 
                                                       .color = BLACK,
                                                       .hidden = true,
                                                       .sec = bps.amountLabel.sec });
  }

  if (bps.cpsLabel.sec != -2) {
    bld->labels.cpsLabel = addLabel(core, (Label) { .text = bld->texts.cps->text,
                                                    .pos = bps.cpsLabel.pos,
                                                    .color = BLACK,
                                                    .hidden = true,
                                                    .sec = bps.cpsLabel.sec });
  }
  // Default Building Buttons
  if (bps.button.sec != -2) {
    bld->buttons.buyButton = addButton(core, (Button) { .text = bld->texts.button->text,
                                                         .rec = bps.button.pos,
                                                         .handler = defBuildButton,
                                                         .ctx = ctx,
                                                         .sec = bps.button.sec });
  }
  
  defBuildingUpdateLabels(bld);
  return core->buildings_size++;
}

