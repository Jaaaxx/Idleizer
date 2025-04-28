#include "idleizer.h"

// Example game 1
int main(void) {
  const int game_width = 1280;
  const int game_height = 800;
  Currency currencies[] = { { "Gold", 0, (Vector2) {200, 200} }, { "Silver", 0, (Vector2) {200, 500} } };
  const int currencies_count = sizeof(currencies) / sizeof(currencies[0]);
  
  const float rectWidth = 200.0f;
  const float rectHeight = 100.0f;

  int gold_miners = 0;
  char gold_miners_label[50];
  sprintf(gold_miners_label, "Gold Miners: %d", gold_miners);

  void goldClickHandler() {
    Currency* cur = &currencies[0]; // find a way to do this without inputting index manually
    cur->amount += 5;
  }
  
  void silverClickHandler() {
    Currency* cur = &currencies[1]; // find a way to do this without inputting index manually
    cur->amount += 1;
  }

  void goldMinerClickHandler() {
    gold_miners++;
    sprintf(gold_miners_label, "Gold Miners: %d", gold_miners);
  }

  void goldMinerHandler() {
    Currency* cur = &currencies[0];
    cur->amount += gold_miners;
  }
  
  Rectangle pbrect = { ((float) game_width - rectWidth - 250) / 2,
                       ((float) game_height - rectHeight) / 2.0f, 
                       (float) rectWidth, (float) rectHeight };
  Rectangle pbrect2 = { ((float) game_width - rectWidth - 250) / 2,
                        ((float) game_height - rectHeight) / 2.0f + rectHeight * 2,
                        (float) rectWidth, (float) rectHeight };
  Rectangle pbrect3 = { ((float) game_width - rectWidth - 100),
                        ((float) 200),
                        (float) rectWidth, (float) rectHeight };
  Ticker tickers[] = { { "Gold Miner", 150, 0, { 700, 200 }, goldMinerHandler } };
  const int tickers_count = sizeof(tickers) / sizeof(tickers[0]);

  Button buttons[] = {
      { &pbrect, "Mine", goldClickHandler },
      { &pbrect2, "Mine silver", silverClickHandler },
      { &pbrect3, "Buy gold miner", goldMinerClickHandler },
  };
  const int btn_count = sizeof(buttons) / sizeof(buttons[0]);

  Label labels[] = {
    { gold_miners_label, { 700, 250 }, 20, BLACK, false }
  };
  const int labels_count = sizeof(labels) / sizeof(labels[0]);

  setupTickers(tickers, tickers_count);
  setupCurrencies(currencies, currencies_count);
  setupButtons(buttons, btn_count);
  setupLabels(labels, labels_count);
  runGame(game_width, game_height);
  return 0;
}
