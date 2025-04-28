#include "idleizer.h"

void runGame(int game_width, int game_height) {
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
}
