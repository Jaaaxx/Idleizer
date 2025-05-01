#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "raylib.h"
#include "currency.h"
#include "ticker.h"
#include "draw.h"
#include "label.h"
#include "core.h"

Section* getSection(Core* core, int idx);

void handleTickers(Core* core);
void mouseButtonsHandler(Core* core, int* mouseBtn);
#endif
