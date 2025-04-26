#include "config.h"

const char* CURRENCY_NAME = "Gold";
const int CURRENCY_AMOUNT_DEFAULT = 0;

const int GAME_WIDTH_INIT = 1280;
const int GAME_HEIGHT_INIT = 800;

const float rectWidth = 200.0f;
const float rectHeight = 100.0f;

Rectangle pbrect = { ((float) GAME_WIDTH_INIT - rectWidth - 250) / 2,
  ((float) GAME_HEIGHT_INIT - rectHeight) / 2.0f, (float) rectWidth, (float) rectHeight };
Button PRIMARY_BUTTON = { &pbrect, "Mine"};
