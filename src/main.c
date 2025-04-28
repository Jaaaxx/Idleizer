#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "config.h"
#include "draw.h"

void mouseButtonsHandler(Button* buttons, int buttons_count, int* mouseBtn) {
  for (int i = 0; i < buttons_count; i++) {
    if (CheckCollisionPointRec(GetMousePosition(), *buttons[i].rec)) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        buttons[i].handler();
        *mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *mouseBtn = -1;
      }
    }
  }
}

int main () {
  int game_width = GAME_WIDTH_INIT;
  int game_height = GAME_HEIGHT_INIT;
 
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(game_width, game_height, "Hello Idleizer");
	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");
 
  char currency_amount_text[100];
  int mouseBtn = -1;
  // game loop
	while (!WindowShouldClose()) {
    // controls
    mouseButtonsHandler(BUTTONS, BUTTONS_COUNT, &mouseBtn);
    // drawing
		BeginDrawing();
		ClearBackground(WHITE);

    drawSectionOutlines(game_width, game_height);
    drawCurrencies(CURRENCIES, CURRENCIES_COUNT);
    drawButtons(BUTTONS, BUTTONS_COUNT);
		DrawTexture(wabbit, 400, 200, WHITE);
		
		EndDrawing();
	}

	UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}
