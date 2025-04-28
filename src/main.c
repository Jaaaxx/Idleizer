#include "idleizer.h"

// Example game 1
int main(void) {
  const int game_width = 1280;
  const int game_height = 800;
  Currency currencies[] = { { "Gold", 0, (Vector2) {200, 200} }, { "Silver", 0, (Vector2) {200, 500} } };
  const int currencies_count = sizeof(currencies) / sizeof(currencies[0]);
  
  const float rectWidth = 200.0f;
  const float rectHeight = 100.0f;

  void goldClickHandler() {
    Currency* cur = &currencies[0]; // find a way to do this without inputting index manually
    cur->amount += 5;
  }
  
  void silverClickHandler() {
    Currency* cur = &currencies[1]; // find a way to do this without inputting index manually
    cur->amount += 5;
  }
  
  Rectangle pbrect = { ((float) game_width - rectWidth - 250) / 2,
                       ((float) game_height - rectHeight) / 2.0f, 
                       (float) rectWidth, (float) rectHeight };
  Rectangle pbrect2 = { ((float) game_width - rectWidth - 250) / 2,
                        ((float) game_height - rectHeight) / 2.0f + rectHeight * 2,
                        (float) rectWidth, (float) rectHeight };
  Button buttons[] = {
      { &pbrect, "Mine", goldClickHandler },
      { &pbrect2, "Mine silver", silverClickHandler },
  };
  const int btn_count = sizeof(buttons) / sizeof(buttons[0]);

  setupCurrencies(currencies, currencies_count);
  setupButtons(buttons, btn_count);
  runGame(game_width, game_height);
  return 0;
}
