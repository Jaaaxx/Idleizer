#include "idleizer.h"

#define game_width 1280
#define game_height 800

typedef struct {
    TextBuffer gold_miners_label;
    TextBuffer gold_miners_cps_label;
    TextBuffer buy_gold_miner_button;
} GameTexts;

typedef struct GameSections {
  Section* gameArea;
  Section* mainArea;
  Section* shopArea;
  Section* displayArea;
  Section* optionsArea;
} GameSections;

typedef struct GameState {
  Core core;
  Currency* gold;
  Currency* silver;
  int gold_miners;
  double gold_miners_cps;
  double gold_miner_cost;
  GameSections* sections;
  GameTexts texts;
} GameState;

static void setGoldMinersLabel(GameState* gs) {
  setTextBuffer(&(gs->texts.gold_miners_label), "Gold Miners: %d", gs->gold_miners);
}

static void setGoldMinersCPSLabel(GameState* gs) {
  setTextBuffer(&(gs->texts.gold_miners_cps_label), "Per Second: %.1f", 
                gs->gold_miners * gs->gold_miners_cps);
}

static void setBuyGoldMinerButtonText(GameState* gs) {
  setTextBuffer(&(gs->texts.buy_gold_miner_button), 
          "Buy gold miner\n Costs %.1f Gold", gs->gold_miner_cost);
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
    gs->core.labels[0].hidden = false;
    gs->core.labels[1].hidden = false;
    gs->core.tickers[0].active = true;
    updateGoldLabels(gs);
  }
}

static void goldMinerHandler(void* ctx) {
  GameState* gs = (GameState*) ctx;
  gs->gold->amount += ((double) gs->gold_miners) * gs->gold_miners_cps / 10.0;
}

static void initSections(GameState* gs) {
  Section* sects = malloc(sizeof(Section) * 5);

  sects[0] = (Section){ { 0, 0, (float)game_width, (float)game_height }, TRANSPARENT };
  sects[1] = (Section){ { 0.0f, 0.0f, 30.0f, 100.0f }, YELLOW, &sects[0] };
  sects[2] = (Section){ { 30, 0, 45, 100 }, BLUE, &sects[0] };
  sects[3] = (Section){ {0, 0, 100, 10}, PURPLE, &sects[2] };
  sects[4] = (Section){ { 75.0f, 0.0f, 25.0f, 100.0f }, GRAY, &sects[0] };

  GameSections* gameSects = malloc(sizeof(GameSections));
  gameSects->gameArea = &sects[0];
  gameSects->mainArea = &sects[1];
  gameSects->displayArea = &sects[2];
  gameSects->optionsArea = &sects[3];
  gameSects->shopArea = &sects[4];

  gs->sections = gameSects;

  setupSections(sects, 5);
  gs->core.sections = sects;
}
static void initCurrencies(GameState* gs) {
  GameSections* secs = gs->sections;
  Currency* currencies = malloc(sizeof(Currency) * 2);

  currencies[0] = (Currency) { "Gold", (double) 0.0, {10, 10}, secs->mainArea };
  currencies[1] = (Currency) { "Silver", (double) 0.0, {60, 10}, secs->mainArea };

  gs->gold = &currencies[0];
  gs->silver = &currencies[1];
  setupCurrencies(currencies, 2);
  gs->core.currencies = currencies;
}

static void initButtons(GameState* gs) {
  GameSections* secs = gs->sections;
  Button* buttons = malloc(sizeof(Button) * 3);
  buttons[0] = (Button) { { 10, 40, 30, 20 }, "Mine", goldClickHandler, gs, secs->mainArea };
  buttons[1] = (Button) { { 60, 40, 30, 20 }, "Mine silver", silverClickHandler, gs, secs->mainArea };
  buttons[2] = (Button) { { 5, 10, 80, 10 }, 
    gs->texts.buy_gold_miner_button.text, goldMinerClickHandler, gs, secs->shopArea };
  setupButtons(buttons, 3);
  gs->core.buttons = buttons;
}

static void initLabels(GameState* gs) { 
  GameSections* secs = gs->sections;
  Label* labels = malloc(sizeof(Label) * 2);
  labels[0] = (Label) { gs->texts.gold_miners_label.text, { 10, 15 }, 20, BLACK, true, secs->displayArea};
  labels[1] = (Label) { gs->texts.gold_miners_cps_label.text, {10, 20}, 20, BLACK, true, secs->displayArea};
  setupLabels(labels, 2);
  gs->core.labels = labels;
}

static void initTickers(GameState* gs) {
  GameSections* secs = gs->sections;
  Ticker* tickers = malloc(sizeof(Ticker) * 1);
  tickers[0] = (Ticker) { "Mining", 6, 0, 0, {50, 17.5f}, goldMinerHandler, gs, secs->displayArea, false};
  setupTickers(tickers, 1);
  gs->core.tickers = tickers;
}

static void destroyGameState(GameState* gs) {
  free(gs->sections->gameArea); 
  free(gs->sections->mainArea); 
  free(gs->sections->shopArea); 
  free(gs->sections);
  destroyCore(&gs->core);
} 

// Example game 1: Mine Hunter
int main(void) {
  GameState gs = {0};
  Core core = {0};
  gs.core = core;
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
