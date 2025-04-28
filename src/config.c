#include "config.h"

Currency CURRENCIES[] = { { "Gold", 0, (Vector2) {200, 200} }, { "Silver", 0, (Vector2) {200, 500} } };
const int CURRENCIES_COUNT = sizeof(CURRENCIES) / sizeof(CURRENCIES[0]);

const int GAME_WIDTH_INIT = 1280;
const int GAME_HEIGHT_INIT = 800;

const float rectWidth = 200.0f;
const float rectHeight = 100.0f;

void goldClickHandler() {
  Currency* cur = &CURRENCIES[0]; // find a way to do this without inputting index manually
  cur->amount += 5;
}

void silverClickHandler() {
  Currency* cur = &CURRENCIES[1]; // find a way to do this without inputting index manually
  cur->amount += 5;
}


Rectangle pbrect = { ((float) GAME_WIDTH_INIT - rectWidth - 250) / 2,
                     ((float) GAME_HEIGHT_INIT - rectHeight) / 2.0f, 
                     (float) rectWidth, (float) rectHeight };
Rectangle pbrect2 = { ((float) GAME_WIDTH_INIT - rectWidth - 250) / 2,
                      ((float) GAME_HEIGHT_INIT - rectHeight) / 2.0f + rectHeight * 2,
                      (float) rectWidth, (float) rectHeight };
Button BUTTONS[] = {
    { &pbrect, "Mine", goldClickHandler },
    { &pbrect2, "Mine silver", silverClickHandler },
};
const int BUTTONS_COUNT = sizeof(BUTTONS) / sizeof(BUTTONS[0]);
