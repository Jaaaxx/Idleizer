#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define CURRENCY_NAME "Money"  
#define GAME_WIDTH 1280
#define GAME_HEIGHT 800

void loadCurrencyText(char* buf, char* currency_name, uint64_t currency_amount); 
void drawSectionOutlines();

int main () {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Idleizer");
	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");
 
  uint64_t currency_amount = 0;
  char currency_amount_text[100];

  // game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

    drawSectionOutlines();

    loadCurrencyText(currency_amount_text, CURRENCY_NAME, currency_amount); 
    DrawText(currency_amount_text, 200, 200, 20, BLACK);

		DrawTexture(wabbit, 400, 200, WHITE);
		
		EndDrawing();
	}

	UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}

void loadCurrencyText(char* buf, char* currency_name, uint64_t currency_amount) {
    sprintf(buf, "%s: %llu", currency_name, currency_amount);
}

void drawSectionOutlines() {
  int divX = GAME_WIDTH / 2;
  DrawLine(divX, 0, divX, GAME_HEIGHT, BLACK);
}
