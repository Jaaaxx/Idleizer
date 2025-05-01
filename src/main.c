#include "idleizer.h"

#define game_width 1280
#define game_height 800

typedef struct BuildingLabels {
  int amountLabel;
  int cpsLabel;
} BuildingLabels;

typedef struct BuildingTickers {
  int mTicker;
} BuildingTickers;

typedef struct BuildingTexts {
  TextBuffer amount;
  TextBuffer cps;
  TextBuffer button;
} BuildingTexts;

typedef struct BuildingVals {
  int amount;
  double cps;
  double cost;
} BuildingVals;

typedef struct {
  TextBuffer flavorText;
} GameTexts;

typedef struct GameSections {
  int gameArea;
  int mainArea;
  int shopArea;
  int displayArea;
  int optionsArea;
} GameSections;

typedef struct GameCurrencies {
  Currency* gold;
  Currency* silver;
} GameCurrencies;

typedef struct GameState {
  Core* core;
  GameCurrencies* currencies;
  GameSections* sections;
  GameTexts texts;
} GameState;

typedef struct BuildingCtx {
  GameState* gs;
  char* name;
  BuildingVals* bv;
  Currency* bCurr;
  Currency* gCurr;
  BuildingLabels* labels;
  BuildingTickers* tickers;
  BuildingTexts* texts;
  int displaySect;
} BuildingCtx;


const char* flavorTexts[] = {
  "I am flavor text! Haha!",
  "Here at mine hunter, we love miners!",
  "Mining is our specialty!",
  "Who said anything about the price of \nsilver?",
  "Woop woop! Mining session!"
};
const int flavorTextsLen = 5;

static void updateFlavorTextLabel(void* ctx) {
  GameState* gs = (GameState*) ctx;

  setTextBuffer(&(gs->texts.flavorText), flavorTexts[GetRandomValue(0, flavorTextsLen-1)]);
}

static void goldClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->currencies->gold->amount += 1;
}

static void silverClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->currencies->silver->amount += 1;
}

static void initSections(GameState* gs) {
  const int count = 5;

  VrRec rects[] = {
    { 0, 0, game_width, game_height },   // gameArea
    { 0.0f, 0.0f, 30.0f, 100.0f }, // mainArea
    { 30.0f, 10.0f, 45.0f, 90.0f }, // displayArea
    { 30.0f, 0.0f, 45.0f, 10.0f }, // optionsArea
    { 75.0f, 0.0f, 25.0f, 100.0f }  // shopArea
  };

  Color colors[] = {
    TRANSPARENT, // gameArea
    YELLOW,      // mainArea
    BLUE,        // displayArea
    PURPLE,      // optionsArea
    GRAY         // shopArea
  };

  int parent_indices[] = {
    -1, // gameArea has no parent
     0, // mainArea → gameArea
     0, // displayArea → gameArea
     0, // optionsArea → displayArea
     0  // shopArea → gameArea
  };

  createSections(gs->core, rects, colors, parent_indices, count);

  GameSections* gameSects = malloc(sizeof(GameSections));
  gameSects->gameArea     = 0;
  gameSects->mainArea     = 1;
  gameSects->displayArea  = 2;
  gameSects->optionsArea  = 3;
  gameSects->shopArea     = 4;

  gs->sections = gameSects;
}

static void initCurrencies(GameState* gs) {
  GameSections* secs = gs->sections;

  int count = 2;

  const char* names[] = { 
    "Gold",
    "Silver" 
  };

  VrVec positions[] = { 
    {10, 10},
    {60, 10} 
  };

  Section* parents[] = { 
    &gs->core->sections[secs->mainArea], 
    &gs->core->sections[secs->mainArea] 
  };

  createCurrencies(gs->core, names, positions, parents, count);
  
  GameCurrencies* gameCurrs = malloc(sizeof(GameCurrencies));
  gameCurrs->gold   = &gs->core->currencies[0];
  gameCurrs->silver = &gs->core->currencies[1];

  gs->currencies = gameCurrs; 
}


static void initButtons(GameState* gs) {
  GameSections* secs = gs->sections;

  const int count = 6;
  
  const char* texts[] = { 
    "Mine Gold", 
    "Mine Silver", 
    "Options", 
    "Stats", 
    "Info", 
    "Legacy"
  };

  VrRec positions[] = { 
    {10, 40, 30, 20}, 
    {60, 40, 30, 20}, 
    {0, 0, 14, 50},
    {0, 50, 14, 50}, 
    {86, 0, 14, 50}, 
    {86, 50, 14, 50} 
  };

  void (*handlers[])(void*) = { 
    goldClickHandler, 
    silverClickHandler, 
    updateFlavorTextLabel, 
    updateFlavorTextLabel,
    updateFlavorTextLabel, 
    updateFlavorTextLabel
  };

  void* ctxs[] = {
    gs,
    gs,
    gs,
    gs,
    gs,
    gs
  };
  
  Section* parents[] = { 
    &gs->core->sections[secs->mainArea], 
    &gs->core->sections[secs->mainArea], 
    &gs->core->sections[secs->optionsArea],
    &gs->core->sections[secs->optionsArea], 
    &gs->core->sections[secs->optionsArea], 
    &gs->core->sections[secs->optionsArea]
  };

  createButtons(gs->core, texts, positions, handlers, ctxs, parents, count);
}


static void initLabels(GameState* gs) { 
  GameSections* secs = gs->sections;
  int count = 1;

  char* texts[] = {
    gs->texts.flavorText.text
  };

  VrVec positions[] = {
    {15, 5}
  };

  Color colors[] = {
    BLACK
  };

  bool hiddens[] = {
    false
  };

  Section* parents[] = {
    &gs->core->sections[secs->optionsArea]
  };

  createLabels(gs->core, texts, positions, colors, hiddens, parents, count);
}


static void initTickers(GameState* gs) {
  GameSections* secs = gs->sections;
  int count = 1;

  char* texts[] = {
    "Updating Flavor Text"
  };

  int frequencies[] = {
    1200
  };

  VrVec positions[] = {
    {0, 0}
  };

  void (*handlers[])(void*) = {
    updateFlavorTextLabel
  };

  void* ctxs[] = {
    gs
  };

  Section* parents[] = {
    &gs->core->sections[secs->gameArea]
  };
  
  bool hiddens[] = {
    true
  };

  createTickers(gs->core, texts, positions, frequencies, handlers, ctxs, parents, hiddens, count);
}

static void destroyGameState(GameState* gs) {
  free(gs->sections);
  destroyCore(gs->core);
}

static void defBuildTicker(void* context) {
  BuildingCtx* ctx = (BuildingCtx*) context;
  ctx->gCurr->amount += ((double) ctx->bv->amount) * ctx->bv->cps / 10.0;
}

static void defBuildingUpdateLabels(BuildingCtx* ctx) {
  setTextBuffer(&(ctx->texts->amount), "%s: %d", ctx->name, ctx->bv->amount);
  setTextBuffer(&(ctx->texts->cps), "Per Second: %.1f %s", ctx->bv->amount*ctx->bv->cps, ctx->gCurr->name);
  setTextBuffer(&(ctx->texts->button), "Buy %s\n Costs %.1f %s", ctx->name,ctx->bv->cost,ctx->bCurr->name);
}

static void defBuildButton(void* context) {
  BuildingCtx* ctx = (BuildingCtx*) context;
  if (ctx->bCurr->amount >= ctx->bv->cost) {
    Core* core = ctx->gs->core;
    ctx->bCurr->amount -= ctx->bv->cost;
    ctx->bv->amount++;
    ctx->bv->cost *= 1.15;
    core->labels[ctx->labels->amountLabel].hidden = false;
    core->labels[ctx->labels->cpsLabel].hidden = false;
    core->tickers[ctx->tickers->mTicker].hidden = false;
    defBuildingUpdateLabels(ctx);
  }
}

static VrVec calcBuildingOffsetPos(int buildings_size, int startX, int startY, int yOffset) {
  VrVec ret = { startX, buildings_size * startY + yOffset };
  return ret; 
}

static VrVec calcNextTickerPos(GameState* gs) {
  return calcBuildingOffsetPos(gs->core->buildings_size, 60, 12, 3);
}

static VrVec calcNextLabelPosAmount(GameState* gs) {
   return calcBuildingOffsetPos(gs->core->buildings_size, 10, 12, 3);
}

static VrVec calcNextLabelPosCPS(GameState* gs) {
  return calcBuildingOffsetPos(gs->core->buildings_size, 10, 12, 8);
}

static VrRec calcNextSectionPos(GameState* gs) {
  VrRec ret = { 0, 15 * gs->core->buildings_size, 100, 10 };
  return ret;
}

static VrRec calcNextButtonPos(GameState* gs) {
  VrRec ret = { 5, 12 * gs->core->buildings_size + 5, 80, 10 };
  return ret;
}


static void setupBuilding(GameState* gs, char* name, double cps, double cost, 
                          Currency* bCurr, Currency* gCurr) {
  BuildingVals* bv = malloc(sizeof(BuildingVals));
  bv->amount = 0;
  bv->cps = cps;
  bv->cost = cost;

  BuildingLabels* bl = malloc(sizeof(BuildingLabels));
  BuildingTickers* btickers = malloc(sizeof(BuildingTickers));

  BuildingCtx* ctx = malloc(sizeof(BuildingCtx)); 
  ctx->gs = gs;
  ctx->name = name;
  ctx->bv = bv;
  ctx->bCurr = bCurr;
  ctx->gCurr = gCurr;
  ctx->labels = bl;
  ctx->tickers = btickers;

  Section* secs = gs->core->sections;

  // Default Building Sections
   ctx->displaySect = addSection(gs->core, calcNextSectionPos(gs), GRAY, 
                                 &secs[gs->sections->displayArea]);

  // Default Building Tickers
  ctx->tickers->mTicker = addTicker(gs->core, name, calcNextTickerPos(gs),
                                    6, defBuildTicker, ctx, true, 
                                    &secs[gs->sections->displayArea]);

  // Default Building Labels
  ctx->texts = malloc(sizeof(BuildingTexts));

  ctx->labels->amountLabel = addLabel(gs->core, ctx->texts->amount.text, calcNextLabelPosAmount(gs), 
                                      BLACK, true, &secs[gs->sections->displayArea]);
  ctx->labels->cpsLabel    = addLabel(gs->core, ctx->texts->cps.text, calcNextLabelPosCPS(gs), 
                                      BLACK, true, &secs[gs->sections->displayArea]);

  // Default Building Buttons 
  addButton(gs->core, ctx->texts->button.text, calcNextButtonPos(gs), 
            defBuildButton, ctx, &secs[gs->sections->shopArea]);

  defBuildingUpdateLabels(ctx);
  
  gs->core->buildings_size++;
}


// Example game 1: Mine Hunter
int main(void) {
  GameState gs = {0};
  Core core = {0};
  gs.core = &core;
  
  initSections(&gs);
  initCurrencies(&gs);
  initButtons(&gs);
  initLabels(&gs);
  initTickers(&gs);

  setupBuilding(&gs, "Gold Miner", 0.08, 5, gs.currencies->silver, gs.currencies->gold);
  setupBuilding(&gs, "Silver Miner", 0.08, 5, gs.currencies->gold, gs.currencies->silver);
  setupBuilding(&gs, "Silver Farm", 1.2, 50, gs.currencies->gold, gs.currencies->silver);
  updateFlavorTextLabel(&gs);

  runGame(&core, game_width, game_height, "Mine Hunter");
  destroyGameState(&gs);
  return 0;
}


// add calculated CPS total under each currency total
// new buildings should create their own sections
// finally, move all of these new changes to engine and organize engine code
