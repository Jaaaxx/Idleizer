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
  int cookies;
} GameCurrencies;

typedef struct GameState {
  Core* core;
  GameCurrencies* currencies;
  GameSections* sections;
  GameTexts texts;
} GameState;
const char *flavorTexts[] = {
    "The scent of fresh dough fills the air.",
    "Your fingers itch for the click.",
    "A strange craving for sugar overtakes you.",
    "You hear the whisper of chocolate chips.",
    "The oven calls to you.",
    "You dreamt of cookies last night.",
    "Flour dust lingers in the sunlight.",
    "You remember your grandmother's secret recipe.",
    "The cookie must rise again.",
    "You feel watched by a giant cookie in the sky.",
    "Your mouse hand twitches involuntarily.",
    "The dough demands attention.",
    "You sense a great baking approaching.",
    "Cookies are love. Cookies are life."
};
const static int flavorTextsLen = 14;

static void updateFlavorTextLabel(void* ctx) {
  GameState* gs = (GameState*) ctx;
  setTextBuffer(&(gs->texts.flavorText), flavorTexts[GetRandomValue(0, flavorTextsLen-1)]);
}

static void initSections(GameState* gs) {
  Color darkBlue = (Color) { 128, 200, 200, 255 };

  Section gameArea = {
    .rec = {0, 0, game_width, game_height},
    .bg = BLANK,
    .parent = -1
  };
  Section mainArea = {
    .rec = {0, 0, 30, 100},
    .bg = darkBlue,
    .parent = 0,
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
    .bg = darkBlue,
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
  Currency cookies = {
    .name = "Cookies",
    .pos = (VrVec) {10, 10},
    .sec = gs->sections->mainArea
  };

  Currency cs[] = { cookies };
  int idx = addCurrencies(gs->core, cs, ARRAY_LEN(cs));
  
  GameCurrencies* gameCurrs = malloc(sizeof(GameCurrencies));
  gameCurrs->cookies= idx + 0;
  gs->currencies = gameCurrs; 
}

static void optionsHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;

  toggleSectionHide(gs->core, gs->sections->mainArea);
}

static void infoHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;

  toggleSectionHide(gs->core, gs->sections->shopArea);
}

static void statsHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;

  toggleSectionHide(gs->core, gs->sections->displayArea);
}

static void initButtons(GameState* gs) {
  Button options = {
    .text = "Options",
    .rec = (VrRec) {0, 0, 14, 50},
    .sec = gs->sections->optionsArea,
    .handler = optionsHandler,
    .ctx = gs,
  };
  Button stats = {
    .text = "Stats",
    .rec = (VrRec) {0, 50, 14, 50},
    .sec = gs->sections->optionsArea,
    .handler = statsHandler,
    .ctx = gs
  };
  Button info = {
    .text = "Info",
    .rec = (VrRec) {86, 0, 14, 50},
    .sec = gs->sections->optionsArea,
    .handler = infoHandler,
    .ctx = gs,
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
    .pos = {15, 5, 70, 100},
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
  if (gs->sections) {
    free(gs->sections);
    gs->sections = NULL;
  }
  
  if (gs->currencies) {
    free(gs->currencies);
    gs->currencies = NULL;
  }

  free(gs->core);
}

static void setupGameBuilding(GameState* gs, char* name, double cps, double cost) {
  Core* core = gs->core;
 
  Building building = newBuilding(core);
  building.vals.cps = cps;
  building.vals.cost = cost;
  building.name = name;
  building.bCurr = gs->currencies->cookies;
  building.gCurr = gs->currencies->cookies;

  // new buildings generate a single section, so this will point to the new building's section
  int newBuildingSec = gs->core->sections_size;
  int bs = core->buildings_size;

  building.positions.section = (BPosRec){ (VrRec) {0, 13 * bs, 100, 13}, gs->sections->displayArea };
  building.positions.ticker = (BPosVec){ (VrVec) {60, 40}, newBuildingSec };
  building.positions.amountLabel = (BPosRec){ (VrRec) {10, 30}, newBuildingSec };
  building.positions.cpsLabel = (BPosRec){ (VrRec) {10, 60}, newBuildingSec };
  building.positions.button = (BPosRec){ (VrRec) {5, 12 * bs + 5, 80, 10}, gs->sections->shopArea };

  addBuilding(core, building);
}

// Example game 1: Mine Hunter
int main(void) {
  GameState gs = {0};

  Core* core = calloc(1, sizeof(Core));
  gs.core = core;
  
  // Initialize the flavor text buffer
  setTextBuffer(&gs.texts.flavorText, "You feel like making cookies. But " 
                                       "nobody wants to eat your cookies.");

  SearchAndSetResourceDir("resources");
 
  initSections(&gs);
  initCurrencies(&gs);
  initButtons(&gs);
  initLabels(&gs);
  initTickers(&gs);

  setupGameBuilding(&gs, "Cursor", 0.1, 15);
  setupGameBuilding(&gs, "Grandma", 1, 100);
  setupGameBuilding(&gs, "Farm", 8, 1100);
  setupGameBuilding(&gs, "Mine", 47, 12000);
  setupGameBuilding(&gs, "Factory", 260, 130000);

  runGame(gs.core, game_width, game_height, "(C)ookie Clicker");
  destroyGameState(&gs);
  
  return 0;
} 
