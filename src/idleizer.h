#ifndef IDLEIZER_H
#define IDLEIZER_H

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "currency.h"
#include "button.h"
#include "game.h"
#include "draw.h"
#include "ticker.h"

void runGame(int game_width, int game_height);

void setupCurrencies(Currency* currencies, int count);
void setupButtons(Button* buttons, int count);
void setupTickers(Ticker* tickers, int count);
void setupLabels(Label* labels, int count);

#endif
