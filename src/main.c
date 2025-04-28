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
    { "Gold", (double) 0.0, {10, 10}, &mainArea },
    { "Silver", (double) 0.0, {60, 10}, &mainArea }
  };
  Currency* gold = &currencies[0];
  Currency* silver = &currencies[1];

  const int currencies_count = sizeof(currencies) / sizeof(currencies[0]);
 
  int gold_miners = 0;
  double gold_miners_cps = 0.08;
  double gold_miner_cost = 5;
  char gold_miners_label[50];
  sprintf(gold_miners_label, "Gold Miners: %d", gold_miners);
  char gold_miners_cps_label[50];
  sprintf(gold_miners_cps_label, "Per Second: %.1f", gold_miners * gold_miners_cps);

  char* buyGoldMinerButtonText = malloc(sizeof(char) * 50);
  sprintf(buyGoldMinerButtonText, "Buy gold miner\n Costs %.1f Silver", gold_miner_cost);
 

  void goldClickHandler() {
    gold->amount += 1;
  }
  
  void silverClickHandler() {
    silver->amount += 1;
  }

  void goldMinerClickHandler() {
    if (silver->amount >= gold_miner_cost) {
      silver->amount -= gold_miner_cost;
      gold_miners++;
      gold_miner_cost *= 1.15;
      sprintf(gold_miners_label, "Gold Miners: %d", gold_miners);
      sprintf(gold_miners_cps_label, "Per Second: %.1f", gold_miners * gold_miners_cps);
      sprintf(buyGoldMinerButtonText, "Buy gold miner\n Costs %.1f Silver", gold_miner_cost);
    }
  }

  void goldMinerHandler() {
    gold->amount += ((double) gold_miners) * gold_miners_cps / 10.0;
  }
  
  Ticker tickers[] = { { "Mining", 6, 0, { 70, 10 }, goldMinerHandler, &shopArea } };
  const int tickers_count = sizeof(tickers) / sizeof(tickers[0]);
 
  Button buttons[] = {
      { { 10, 40, 30, 20 }, "Mine", goldClickHandler, &mainArea },
      { { 60, 40, 30, 20 }, "Mine silver", silverClickHandler, &mainArea },
      { { 5, 10, 30, 10 }, buyGoldMinerButtonText, goldMinerClickHandler, &shopArea },
  };

  const int btn_count = sizeof(buttons) / sizeof(buttons[0]);

  Label labels[] = {
    { gold_miners_label, { 40, 10 }, 20, BLACK, false, &shopArea },
    { gold_miners_cps_label, {40, 15}, 20, BLACK, false, &shopArea }
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
