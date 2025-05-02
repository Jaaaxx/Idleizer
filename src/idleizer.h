#ifndef IDLEIZER_H
#define IDLEIZER_H

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#include "currency.h"
#include "button.h"
#include "game.h"
#include "ticker.h"
#include "section.h"
#include "core.h"
#include "text_buffer.h"
#include "building.h"

// Core loop and lifecycle
void runGame(Core* core, int game_width, int game_height, char* title);
void freeAll(Core* core);

#endif
