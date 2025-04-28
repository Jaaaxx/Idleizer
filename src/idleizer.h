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
#include "handlers.h"

void runGame(int game_width, int game_height);
#endif
