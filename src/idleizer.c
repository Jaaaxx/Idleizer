#include "idleizer.h"

void runGame(int game_width, int game_height) {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  SetTargetFPS(60);

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
    drawLabels(LABELS, LABELS_COUNT);
    drawCurrencies(CURRENCIES, CURRENCIES_COUNT);
    drawButtons(BUTTONS, BUTTONS_COUNT);
    handleTickers(TICKERS, TICKERS_COUNT);
		DrawTexture(wabbit, 400, 200, WHITE);
		
		EndDrawing();
	}

	UnloadTexture(wabbit);
	CloseWindow();
}

void setupCurrencies(Currency* currencies, int count) {
  CURRENCIES = currencies;
  CURRENCIES_COUNT = count;
}

void setupButtons(Button* buttons, int count) {
  BUTTONS = buttons;
  BUTTONS_COUNT = count;
}

void setupTickers(Ticker* tickers, int count) {
  TICKERS = tickers;
  TICKERS_COUNT = count;
}

void setupLabels(Label* labels, int count) {
  LABELS = labels;
  LABELS_COUNT = count;
}
