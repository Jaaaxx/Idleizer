#include "idleizer.h"

#define game_width 1280
#define game_height 800

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
  int gold;
  int silver;
} GameCurrencies;

typedef struct GameState {
  Core* core;
  GameCurrencies* currencies;
  GameSections* sections;
  GameTexts texts;
} GameState;

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

  bool hiddens[] = {
    false,
    false,
    false,
    false,
    false
  };

  int parent_indices[] = {
    -1, // gameArea has no parent
     0, // mainArea → gameArea
     0, // displayArea → gameArea
     0, // optionsArea → displayArea
     0  // shopArea → gameArea
  };

  addSections(gs->core, rects, colors, parent_indices, hiddens, count);

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

  bool hiddens[] = {
    false,
    false
  };

  int parents[] = { 
    secs->mainArea, 
    secs->mainArea 
  };

  addCurrencies(gs->core, names, positions, parents, hiddens, count);
  
  GameCurrencies* gameCurrs = malloc(sizeof(GameCurrencies));
  gameCurrs->gold   = 0;
  gameCurrs->silver = 1;

  gs->currencies = gameCurrs; 
}


static void initButtons(GameState* gs) {
  GameSections* secs = gs->sections;

  const int count = 4;
  
  const char* texts[] = { 
    "Options", 
    "Stats", 
    "Info", 
    "Legacy"
  };

  VrRec positions[] = { 
    {0, 0, 14, 50},
    {0, 50, 14, 50}, 
    {86, 0, 14, 50}, 
    {86, 50, 14, 50} 
  };

  void (*handlers[])(void*) = { 
    updateFlavorTextLabel, 
    updateFlavorTextLabel,
    updateFlavorTextLabel, 
    updateFlavorTextLabel
  };

  void* ctxs[] = {
    gs,
    gs,
    gs,
    gs
  };

  bool hiddens[] = {
    false,
    false,
    false,
    false
  };
  
  int parents[] = { 
    secs->optionsArea,
    secs->optionsArea, 
    secs->optionsArea, 
    secs->optionsArea
  };

  addButtons(gs->core, texts, positions, handlers, ctxs, parents, hiddens, count);
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

  int parents[] = {
    secs->optionsArea
  };

  addLabels(gs->core, texts, positions, colors, hiddens, parents, count);
}


static void initTickers(GameState* gs) {
  GameSections* secs = gs->sections;
  int count = 1;

  char* texts[] = {
    "Updating Flavor Text",
  };

  int frequencies[] = {
    1200,
  };

  VrVec positions[] = {
    {0, 0},
  };

  void (*handlers[])(void*) = {
    updateFlavorTextLabel,
  };

  void* ctxs[] = {
    gs,
  };

  int parents[] = {
    secs->gameArea,
  };
  
  bool hiddens[] = {
    true,
  };

  addTickers(gs->core, texts, positions, frequencies, handlers, ctxs, parents, hiddens, count);
}

static void destroyGameState(GameState* gs) {
  free(gs->sections);
  destroyCore(gs->core);
}

static VrVec calcNextTickerPos(Core* core) {
  return calcBuildingOffsetPos(core->buildings_size, 60, 12, 3);
}

static VrVec calcNextLabelPosAmount(Core* core) {
   return calcBuildingOffsetPos(core->buildings_size, 10, 12, 3);
}

static VrVec calcNextLabelPosCPS(Core* core) {
  return calcBuildingOffsetPos(core->buildings_size, 10, 12, 8);
}

static VrRec calcNextSectionPos(Core* core) {
  VrRec ret = { 0, 13 * core->buildings_size, 100, 13 };
  return ret;
}

static VrRec calcNextButtonPos(Core* core) {
  VrRec ret = { 5, 12 * core->buildings_size + 5, 80, 10 };
  return ret;
}

void setupGameBuilding(GameState* gs, char* name, double cps, double cost, int bCurr, int gCurr) {
  BuildingPositions bpos = {0};
  Core* core = gs->core;
  bpos.ticker = &(BuildingPositionVec){ calcNextTickerPos(core), gs->sections->displayArea };
  bpos.amountLabel = &(BuildingPositionVec){ calcNextLabelPosAmount(core), gs->sections->displayArea };
  bpos.cpsLabel = &(BuildingPositionVec){ calcNextLabelPosCPS(core), gs->sections->displayArea };
  bpos.button = &(BuildingPositionRec){ calcNextButtonPos(core), gs->sections->shopArea };
  bpos.section = &(BuildingPositionRec){ calcNextSectionPos(core), gs->sections->displayArea };

  setupBuilding(core, name, cps, cost, bCurr, gCurr, bpos, gs);
}

// Example game 1: Mine Hunter
int main(void) {
  GameState gs = {0};
  gs.core = &(Core){0};

  initSections(&gs);
  initCurrencies(&gs);
  initButtons(&gs);
  initLabels(&gs);
  initTickers(&gs);

  setupGameBuilding(&gs, "Gold Miner", 0.08, 5, gs.currencies->silver, gs.currencies->gold);
  setupGameBuilding(&gs, "Silver Miner", 0.08, 5, gs.currencies->gold, gs.currencies->silver);
  setupGameBuilding(&gs, "Silver Farm", 1.2, 50, gs.currencies->gold, gs.currencies->silver);
  updateFlavorTextLabel(&gs);

  runGame(gs.core, game_width, game_height, "Mine Hunter");
  destroyGameState(&gs);
  return 0;
}
