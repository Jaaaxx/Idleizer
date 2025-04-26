#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "config.h"
#include "draw.h"

int main () {
  int game_width = GAME_WIDTH_INIT;
  int game_height = GAME_HEIGHT_INIT;
 
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(game_width, game_height, "Hello Idleizer");
	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");
 
  int currency_amount = CURRENCY_AMOUNT_DEFAULT;
  char currency_amount_text[100];
  int mouseBtn = -1;
  // game loop
	while (!WindowShouldClose()) {
    // controls
    if (CheckCollisionPointRec(GetMousePosition(), *PRIMARY_BUTTON.rect)) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mouseBtn != 1) {
        currency_amount++;
        mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        mouseBtn = -1;
      }
    }
    // drawing
		BeginDrawing();
		ClearBackground(WHITE);

    drawSectionOutlines(game_width, game_height);

    sprintf(currency_amount_text, "%s: %llu", CURRENCY_NAME, currency_amount);
    DrawText(currency_amount_text, 200, 200, 20, RED);
    drawButton(&PRIMARY_BUTTON);
		DrawTexture(wabbit, 400, 200, WHITE);
		
		EndDrawing();
	}

	UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}
