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
  int upgradesArea;
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
  Section upgradesArea = {
    .rec = {75, 0, 25, 15},
    .bg = darkBlue,
    .parent = 0
  };
  Section shopArea = {
    .rec = {75, 15, 25, 85},
    .bg = darkBlue,
    .parent = 0
  };

  Section ss[] = { gameArea, mainArea, displayArea, optionsArea, upgradesArea, shopArea };
  int idx = addSections(gs->core, ss, ARRAY_LEN(ss));

  GameSections* gameSects = malloc(sizeof(GameSections));
  gameSects->gameArea     = idx + 0;
  gameSects->mainArea     = idx + 1;
  gameSects->displayArea  = idx + 2;
  gameSects->optionsArea  = idx + 3;
  gameSects->upgradesArea = idx + 4;
  gameSects->shopArea     = idx + 5;
  gs->sections = gameSects;
}

typedef struct CookieSizeParams {
  VrRec newRec;
  GameState* gs;
} CookieSizeParams;

static void setCookieSize(void* ctx) {
  CookieSizeParams* cs = (CookieSizeParams*) ctx;
  GameState* gs = cs->gs;
  Core* core = gs->core;
  Currency* cr = &core->currencies[gs->currencies->cookies];
  Button* b = &core->buttons[cr->_button];
  b->rec = cs->newRec;
}

static void cookieClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  Currency* curr = &gs->core->currencies[gs->currencies->cookies];
  Button* b = &gs->core->buttons[curr->_button];

  static int listener = -1;
 
  static CookieSizeParams pmNormal = {0};
  static CookieSizeParams pmShrunk = {0};
  
  // Only initialize these parameters once, and make sure the button rect values are valid
  if (pmNormal.gs == NULL && b != NULL) {
    // Ensure all rect values are initialized to valid defaults if they're zero
    VrRec safeRec = b->rec;
    if (safeRec.x == 0) safeRec.x = 10;
    if (safeRec.y == 0) safeRec.y = 30;
    if (safeRec.w == 0) safeRec.w = 80;
    if (safeRec.h == 0) safeRec.h = 40;
    
    pmNormal = (CookieSizeParams) { safeRec, gs };
    pmShrunk = (CookieSizeParams) { 
      (VrRec) { 
        safeRec.x * 1.1, 
        safeRec.y * 1.05, 
        safeRec.w * 0.9, 
        safeRec.h * 0.9 
      }, 
      gs 
    }; 
  }
 
  setCookieSize(&pmShrunk);

  listener = addMouseEventListener(listener, MOUSE_BUTTON_LEFT, MOUSE_EVENT_RELEASE, 
                                   setCookieSize, &pmNormal, false);

  curr->amount += curr->perClick;
}

static void initCurrencies(GameState* gs) {
  Currency cookies = {
    .name = "Cookies",
    .pos = (VrVec) {30, 10},
    .sec = gs->sections->mainArea,
    .button = (Button) { .rec = (VrRec) {10, 30, 80, 40},
                         .image = LoadResourceImage("images/cookie.png"),
                         .handler = cookieClickHandler,
                         .ctx = gs },
    .amountLabel = (Label) { .fontSize = 30, },
    .cpsLabel = (Label) { .fontSize = 25, .color = DARKGRAY }
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

typedef struct UpgradeContext {
  GameState* gs;
  int button;
} UpgradeContext;

static void doubleCPSHandler(void* ctx) {
  UpgradeContext* uctx = (UpgradeContext*) ctx;
  GameState* gs = uctx->gs;
  static bool bought = false;
  Currency* curr = &gs->core->currencies[gs->currencies->cookies];
  if (!bought && curr->amount >= 100) {
    curr->amount -= 100;
    curr->cpsMult += 1;
    bought = true;
    gs->core->buttons[uctx->button].hidden = true;
  }
  free(ctx);
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

  UpgradeContext* uctx = malloc(sizeof(UpgradeContext));
  uctx->gs = gs;
  uctx->button = 5;

  Button upgrade1 = {
    .text = "Double CPS",
    .rec = (VrRec) {10, 10, 20, 40},
    .sec = gs->sections->upgradesArea,
    .handler = doubleCPSHandler,
    .ctx = uctx
  };

  Button bs[] = { options, stats, info, legacy, upgrade1 };
  addButtons(gs->core, bs, ARRAY_LEN(bs));
}


static void initLabels(GameState* gs) { 
  GameSections* secs = gs->sections;

  Label flavorText = {
    .text = gs->texts.flavorText.text,
    .color = BLACK,
    .pos = {15, 5, 70, 100},
    .sec = secs->optionsArea,
    .fontSize = 20 
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

// Example game 2: Cookie Clicker
int main(void) {
  GameState gs = {0};

  Core* core = calloc(1, sizeof(Core));
  gs.core = core;
  
  // Initialize the flavor text buffer
  setTextBuffer(&gs.texts.flavorText, "You feel like making cookies. But " 
                                       "nobody wants to eat your cookies.");


  
  setDefaultFontResource("fonts/Merriweather-Regular.ttf");

  InitResourcePaths();

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
