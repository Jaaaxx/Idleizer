#include "idleizer.h"

#define game_width 1280
#define game_height 800

typedef struct GameSections {
  Section* gameArea;
  Section* mainArea;
  Section* shopArea;
} GameSections;

typedef struct GameState {
  Currency* gold;
  Currency* silver;
  int gold_miners;
  double gold_miners_cps;
  double gold_miner_cost;
  char gold_miners_label[50];
  char gold_miners_cps_label[50];
  char buyGoldMinerButtonText[50];
  GameSections* sections;
} GameState;

static void setGoldMinersLabel(GameState* gs) {
  sprintf(gs->gold_miners_label, "Gold Miners: %d", gs->gold_miners);
}

static void setGoldMinersCPSLabel(GameState* gs) {
  sprintf(gs->gold_miners_cps_label, "Per Second: %.1f", gs->gold_miners * gs->gold_miners_cps);
}

static void setBuyGoldMinerButtonText(GameState* gs) {
  sprintf(gs->buyGoldMinerButtonText, "Buy gold miner\n Costs %.1f Gold", gs->gold_miner_cost);
}

static void updateGoldLabels(GameState* gs) {
  setGoldMinersLabel(gs);
  setGoldMinersCPSLabel(gs);
  setBuyGoldMinerButtonText(gs);
}

static void goldClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->gold->amount += 1;
}

static void silverClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->silver->amount += 1;
}

static void goldMinerClickHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  if (gs->gold->amount >= gs->gold_miner_cost) {
    gs->gold->amount -= gs->gold_miner_cost;
    gs->gold_miners++;
    gs->gold_miner_cost *= 1.15;
    updateGoldLabels(gs);
  }
}

static void goldMinerHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->gold->amount += ((double) gs->gold_miners) * gs->gold_miners_cps / 10.0;
}

static void initSections(GameState* gs) {
  Section* sects = malloc(sizeof(Section) * 3);

  sects[0] = (Section){ { 0, 0, (float)game_width, (float)game_height }, TRANSPARENT };
  sects[1] = (Section){ { 0.0f, 0.0f, 50.0f, 100.0f }, YELLOW, &sects[0] };
  sects[2] = (Section){ { 50.0f, 0.0f, 50.0f, 100.0f }, GRAY, &sects[0] };

  GameSections* gameSects = malloc(sizeof(GameSections));
  gameSects->gameArea = &sects[0];
  gameSects->mainArea = &sects[1];
  gameSects->shopArea = &sects[2];

  gs->sections = gameSects;

  setupSections(sects, 3);
}
static void initCurrencies(GameState* gs) {
  GameSections* secs = gs->sections;
  Currency* currencies = malloc(sizeof(Currency) * 2);

  currencies[0] = (Currency) { "Gold", (double) 0.0, {10, 10}, secs->mainArea };
  currencies[1] = (Currency) { "Silver", (double) 0.0, {60, 10}, secs->mainArea };

  gs->gold = &currencies[0];
  gs->silver = &currencies[1];
  setupCurrencies(currencies, 2);
}

static void initButtons(GameState* gs) {
  GameSections* secs = gs->sections;
  Button* buttons = malloc(sizeof(Button) * 3);
  buttons[0] = (Button) { { 10, 40, 30, 20 }, "Mine", goldClickHandler, gs, secs->mainArea };
  buttons[1] = (Button) { { 60, 40, 30, 20 }, "Mine silver", silverClickHandler, gs, secs->mainArea };
  buttons[2] = (Button) { { 5, 10, 30, 10 }, 
    gs->buyGoldMinerButtonText, goldMinerClickHandler, gs, secs->shopArea };
  setupButtons(buttons, 3);
}

static void initLabels(GameState* gs) { 
  GameSections* secs = gs->sections;
  Label* labels = malloc(sizeof(Label) * 2);
  labels[0] = (Label) { gs->gold_miners_label, { 40, 10 }, 20, BLACK, false, secs->shopArea };
  labels[1] = (Label) { gs->gold_miners_cps_label, {40, 15}, 20, BLACK, false, secs->shopArea };
  setupLabels(labels, 2);
}

static void initTickers(GameState* gs) {
  GameSections* secs = gs->sections;
  Ticker* tickers = malloc(sizeof(Ticker) * 1);
  tickers[0] = (Ticker) { "Mining", 6, 0, { 70, 10 }, goldMinerHandler, gs, secs->shopArea };
  setupTickers(tickers, 1);
}

static void destroyGameState(GameState* gs) {
  free(gs->sections->gameArea); 
  free(gs->sections->mainArea); 
  free(gs->sections->shopArea); 
  free(gs->sections);
}

// Example game 1: Mine Hunter
int main(void) {
  GameState gs = {0};

  gs.gold_miners = 0;
  gs.gold_miners_cps = 0.08;
  gs.gold_miner_cost = 5;
  
  initSections(&gs);
  initCurrencies(&gs);
  initButtons(&gs);
  initLabels(&gs);
  initTickers(&gs);

  updateGoldLabels(&gs);

  runGame(game_width, game_height, "Mine Hunter");
  destroyGameState(&gs);
  return 0;
}
