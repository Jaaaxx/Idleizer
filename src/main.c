#include "idleizer.h"

#define game_width 1280
#define game_height 800
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

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

const static char* flavorTexts[] = {
  "I am flavor text! Haha!",
  "Here at mine hunter, we love miners!",
  "Mining is our specialty!",
  "Who said anything about the price of \nsilver?",
  "Woop woop! Mining session!"
};
const static int flavorTextsLen = 5;

static void updateFlavorTextLabel(void* ctx) {
  GameState* gs = (GameState*) ctx;
  setTextBuffer(&(gs->texts.flavorText), flavorTexts[GetRandomValue(0, flavorTextsLen-1)]);
}

static void initSections(GameState* gs) {
  Section gameArea = {
    .rec = {0, 0, game_width, game_height},
    .bg = BLANK,
    .parent = -1
  };
  Section mainArea = {
    .rec = {0, 0, 30, 100},
    .bg = YELLOW,
    .parent = 0
  };
  Section displayArea = {
    .rec = {30, 10, 45, 90},
    .bg = BLUE,
    .parent = 0
  };
  Section optionsArea = {
    .rec = {30, 0, 45, 10},
    .bg = PURPLE,
    .parent = 0
  };
  Section shopArea = {
    .rec = {75, 0, 25, 100},
    .bg = GRAY,
    .parent = 0
  };

  Section ss[] = { gameArea, mainArea, displayArea, optionsArea, shopArea };
  int idx = addSections(gs->core, ss, ARRAY_LEN(ss));

  GameSections* gameSects = malloc(sizeof(GameSections));
  gameSects->gameArea     = idx + 0;
  gameSects->mainArea     = idx + 1;
  gameSects->displayArea  = idx + 2;
  gameSects->optionsArea  = idx + 3;
  gameSects->shopArea     = idx + 4;
  gs->sections = gameSects;
}

static void initCurrencies(GameState* gs) {
  Currency gold = {
    .name = "Gold",
    .pos = (VrVec) {10, 10},
    .sec = gs->sections->mainArea
  };
  Currency silver = {
    .name = "Silver",
    .pos = (VrVec) {60, 10},
    .sec = gs->sections->mainArea
  };

  Currency cs[] = { gold, silver };
  int idx = addCurrencies(gs->core, cs, ARRAY_LEN(cs));
  
  GameCurrencies* gameCurrs = malloc(sizeof(GameCurrencies));
  gameCurrs->gold   = idx + 0;
  gameCurrs->silver = idx + 1;
  gs->currencies = gameCurrs; 
}


static void initButtons(GameState* gs) {
  Button options = {
    .text = "Options",
    .rec = (VrRec) {0, 0, 14, 50},
    .sec = gs->sections->optionsArea
  };
  Button stats = {
    .text = "Stats",
    .rec = (VrRec) {0, 50, 14, 50},
    .sec = gs->sections->optionsArea
  };
  Button info = {
    .text = "Info",
    .rec = (VrRec) {86, 0, 14, 50},
    .sec = gs->sections->optionsArea
  };
  Button legacy = {
    .text = "Legacy",
    .rec = (VrRec) {86, 50, 14, 50},
    .sec = gs->sections->optionsArea
  };

  Button bs[] = { options, stats, info, legacy };
  addButtons(gs->core, bs, ARRAY_LEN(bs));
}


static void initLabels(GameState* gs) { 
  GameSections* secs = gs->sections;

  Label flavorText = {
    .text = gs->texts.flavorText.text,
    .color = BLACK,
    .pos = {15, 5},
    .sec = secs->optionsArea
  };

  Label ls[] = { flavorText };
  addLabels(gs->core, ls, ARRAY_LEN(ls)); 
}


static void initTickers(GameState* gs) {
  Ticker flavorTextUpdate = {
    .name = "Updating Flavor Text",
    .frequency = 1200,
    .handler = updateFlavorTextLabel,
    .ctx = gs,
    .hidden = true
  };

  Ticker ts[] = { flavorTextUpdate };
  addTickers(gs->core, ts, ARRAY_LEN(ts)); 
}

static void destroyGameState(GameState* gs) {
  free(gs->sections);
  free(gs->currencies);
  freeAll(gs->core);
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

static void setupGameBuilding(GameState* gs, char* name, double cps, double cost, int bCurr, int gCurr) {
  Core* core = gs->core;
 
  Building building = newBuilding(core);
  building.vals.cps = cps;
  building.vals.cost = cost;
  building.name = name;
  building.bCurr = bCurr;
  building.gCurr = gCurr;
  building.positions.ticker = (BPosVec){ calcNextTickerPos(core), gs->sections->displayArea };
  building.positions.amountLabel = (BPosVec){ calcNextLabelPosAmount(core), gs->sections->displayArea };
  building.positions.cpsLabel = (BPosVec){ calcNextLabelPosCPS(core), gs->sections->displayArea };
  building.positions.button = (BPosRec){ calcNextButtonPos(core), gs->sections->shopArea };
  building.positions.section = (BPosRec){ calcNextSectionPos(core), gs->sections->displayArea };

  addBuilding(core, building);
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
  setupGameBuilding(&gs, "Gold Farm", 1.2, 50, gs.currencies->silver, gs.currencies->gold);
  updateFlavorTextLabel(&gs);

  runGame(gs.core, game_width, game_height, "Mine Hunter");
  destroyGameState(&gs);
  return 0;
}
