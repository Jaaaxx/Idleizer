#include "idleizer.h"

// Example game 1: Mine Hunter
int main(void) {
  const int game_width = 1280;
  const int game_height = 800;
 
  // Sections (must be declared first)
  Section gameArea = { { 0, 0, (float) game_width, (float) game_height}, RED };
  Section mainArea = { { 0.0f, 0.0f, 50.0f, 100.0f }, YELLOW, &gameArea };
  Section shopArea = { { 50.0f, 0.0f, 50.0f, 100.0f }, GRAY, &gameArea };
  Section sections[] = { mainArea, shopArea };
  const int sections_count = sizeof(sections) / sizeof(sections[0]);

  Currency currencies[] = {
    { "Gold", 0, {10, 10}, &mainArea },
    { "Silver", 0, {60, 10}, &mainArea }
  };
  Currency* gold = &currencies[0];
  Currency* silver = &currencies[1];

  const int currencies_count = sizeof(currencies) / sizeof(currencies[0]);
 
  int gold_miners = 0;
  char gold_miners_label[50];
  sprintf(gold_miners_label, "Gold Miners: %d", gold_miners);

  void goldClickHandler() {
    gold->amount += 1;
  }
  
  void silverClickHandler() {
    silver->amount += 1;
  }

  void goldMinerClickHandler() {
    if (silver->amount >= 5) {
      silver->amount -= 5;
      gold_miners++;
      sprintf(gold_miners_label, "Gold Miners: %d", gold_miners);
    }
  }

  void goldMinerHandler() {
    gold->amount += gold_miners;
  }
  
  Ticker tickers[] = { { "Mining", 150, 0, { 70, 10 }, goldMinerHandler, &shopArea } };
  const int tickers_count = sizeof(tickers) / sizeof(tickers[0]);

  Button buttons[] = {
      { { 10, 40, 30, 20 }, "Mine", goldClickHandler, &mainArea },
      { { 60, 40, 30, 20 }, "Mine silver", silverClickHandler, &mainArea },
      { { 5, 10, 30, 10 }, "Buy gold miner\n Costs 5 Silver", goldMinerClickHandler, &shopArea },
  };
  const int btn_count = sizeof(buttons) / sizeof(buttons[0]);

  Label labels[] = {
    { gold_miners_label, { 40, 10 }, 20, BLACK, false, &shopArea }
  };
  const int labels_count = sizeof(labels) / sizeof(labels[0]);

  setupSections(sections, sections_count);
  setupTickers(tickers, tickers_count);
  setupCurrencies(currencies, currencies_count);
  setupButtons(buttons, btn_count);
  setupLabels(labels, labels_count);
  runGame(game_width, game_height, "Mine Hunter");
  return 0;
}
