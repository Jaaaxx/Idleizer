#include "idleizer.h"

#define game_width 1280
#define game_height 800

typedef struct BuildingTexts {
  TextBuffer amount;
  TextBuffer cps;
  TextBuffer button;
} CurrencyTexts;

typedef struct BuildingVals {
  int amount;
  double cps;
  double cost;
} BuildingVals;

typedef struct {
  CurrencyTexts goldMiners;
  TextBuffer flavorText;
} GameTexts;

typedef struct GameSections {
  Section* gameArea;
  Section* mainArea;
  Section* shopArea;
  Section* displayArea;
  Section* optionsArea;
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
  
  // Buildings
  BuildingVals goldMiners;
} GameState;

const char* flavorTexts[] = {
  "I am flavor text! Haha!",
  "Here at mine hunter, we love miners!",
  "Mining is our specialty!",
  "Who said anything about the price of \nsilver?",
  "Woop woop! Mining session!"
};
const int flavorTextsLen = 5;

static void setGoldMinersLabel(GameState* gs) {
  setTextBuffer(&(gs->texts.goldMiners.amount), "Gold Miners: %d", gs->goldMiners.amount);
}

static void setGoldMinersCPSLabel(GameState* gs) {
  setTextBuffer(&(gs->texts.goldMiners.cps), "Per Second: %.1f", 
                gs->goldMiners.amount * gs->goldMiners.cps);
}

static void setBuyGoldMinerButtonText(GameState* gs) {
  setTextBuffer(&(gs->texts.goldMiners.button), 
          "Buy gold miner\n Costs %.1f Gold", gs->goldMiners.cost);
}

static void updateFlavorTextLabel(void* ctx) {
  GameState* gs = (GameState*) ctx;

  setTextBuffer(&(gs->texts.flavorText), flavorTexts[GetRandomValue(0, flavorTextsLen-1)]);
}

static void updateGoldLabels(GameState* gs) {
  setGoldMinersLabel(gs);
  setGoldMinersCPSLabel(gs);
  setBuyGoldMinerButtonText(gs);
}

static void goldClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->currencies->gold->amount += 1;
}

static void silverClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->currencies->silver->amount += 1;
}

static void goldMinerClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  if (gs->currencies->gold->amount >= gs->goldMiners.cost) {
    gs->currencies->gold->amount -= gs->goldMiners.cost;
    gs->goldMiners.amount++;
    gs->goldMiners.cost *= 1.15;
    gs->core->labels[0].hidden = false;
    gs->core->labels[1].hidden = false;
    gs->core->tickers[0].hidden = false;
    updateGoldLabels(gs);
  }
}

static void goldMinerHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->currencies->gold->amount += ((double) gs->goldMiners.amount) * gs->goldMiners.cps / 10.0;
}


static void initSections(GameState* gs) {
  const int count = 5;

  VrRec rects[] = {
    { 0, 0, game_width, game_height },   // gameArea
    { 0.0f, 0.0f, 30.0f, 100.0f }, // mainArea
    { 30.0f, 0.0f, 45.0f, 100.0f }, // displayArea
    { 0.0f, 0.0f, 100.0f, 10.0f }, // optionsArea
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
     2, // optionsArea → displayArea
     0  // shopArea → gameArea
  };

  createSections(gs->core, rects, colors, parent_indices, count);

  GameSections* gameSects = malloc(sizeof(GameSections));
  gameSects->gameArea     = &gs->core->sections[0];
  gameSects->mainArea     = &gs->core->sections[1];
  gameSects->displayArea  = &gs->core->sections[2];
  gameSects->optionsArea  = &gs->core->sections[3];
  gameSects->shopArea     = &gs->core->sections[4];

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
    secs->mainArea, 
    secs->mainArea 
  };

  createCurrencies(gs->core, names, positions, parents, count);
  
  GameCurrencies* gameCurrs = malloc(sizeof(GameCurrencies));
  gameCurrs->gold   = &gs->core->currencies[0];
  gameCurrs->silver = &gs->core->currencies[1];

  gs->currencies = gameCurrs; 
}


static void initButtons(GameState* gs) {
  GameSections* secs = gs->sections;

  const int count = 7;
  
  const char* texts[] = { 
    "Mine Gold", 
    "Mine Silver", 
    gs->texts.goldMiners.button.text,
    "Options", 
    "Stats", 
    "Info", 
    "Legacy"
  };

  VrRec positions[] = { 
    {10, 40, 30, 20}, 
    {60, 40, 30, 20}, 
    {5, 5, 80, 10}, 
    {0, 0, 14, 50},
    {0, 50, 14, 50}, 
    {86, 0, 14, 50}, 
    {86, 50, 14, 50} 
  };

  void (*handlers[])(void*) = { 
    goldClickHandler, 
    silverClickHandler, 
    goldMinerClickHandler,
    updateFlavorTextLabel, 
    updateFlavorTextLabel,
    updateFlavorTextLabel, 
    updateFlavorTextLabel
  };
  
  Section* parents[] = { 
    secs->mainArea, 
    secs->mainArea, 
    secs->shopArea, 
    secs->optionsArea,
    secs->optionsArea, 
    secs->optionsArea, 
    secs->optionsArea
  };

  createButtons(gs->core, texts, positions, handlers, gs, parents, count);
}


static void initLabels(GameState* gs) { 
  GameSections* secs = gs->sections;
  int count = 3;

  char* texts[] = {
    gs->texts.goldMiners.amount.text,
    gs->texts.goldMiners.cps.text,
    gs->texts.flavorText.text
  };

  VrVec positions[] = {
    {10, 15},
    {10, 20},
    {15, 5}
  };

  Color colors[] = {
    BLACK,
    BLACK,
    BLACK
  };

  bool hiddens[] = {
    true,
    true,
    false
  };

  Section* parents[] = {
    secs->displayArea,
    secs->displayArea,
    secs->optionsArea
  };

  createLabels(gs->core, texts, positions, colors, hiddens, parents, count);
}


static void initTickers(GameState* gs) {
  GameSections* secs = gs->sections;
  int count = 2;

  char* texts[] = {
    "Mining",
    "Updating Flavor Text"
  };

  int frequencies[] = {
    6,
    1200
  };

  VrVec positions[] = {
    {60, 17.5f},
    {0, 0}
  };

  void (*handlers[])(void*) = {
    goldMinerHandler,
    updateFlavorTextLabel
  };

  Section* parents[] = {
    secs->displayArea,
    secs->gameArea
  };
  
  bool hiddens[] = {
    true,
    true
  };

  createTickers(gs->core, texts, positions, frequencies, handlers, gs, parents, hiddens, count);
}

static void destroyGameState(GameState* gs) {
  free(gs->sections->gameArea); 
  free(gs->sections->mainArea); 
  free(gs->sections->shopArea); 
  free(gs->sections);
  destroyCore(gs->core);
}

// Example game 1: Mine Hunter
int main(void) {
  GameState gs = {0};
  Core core = {0};
  gs.core = &core;
  gs.goldMiners.amount = 0;
  gs.goldMiners.cps = 0.08;
  gs.goldMiners.cost = 5;
  
  initSections(&gs);
  initCurrencies(&gs);
  initButtons(&gs);
  initLabels(&gs);
  initTickers(&gs);

  updateGoldLabels(&gs);
  updateFlavorTextLabel(&gs);

  runGame(&core, game_width, game_height, "Mine Hunter");
  destroyGameState(&gs);
  return 0;
}
