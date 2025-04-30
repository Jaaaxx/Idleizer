#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "raylib.h"
#include "currency.h"
#include "ticker.h"
#include "draw.h"
#include "label.h"
#include "core.h"

void handleTickers();
void mouseButtonsHandler(Button* buttons, int buttons_count, int* mouseBtn);
#endif
