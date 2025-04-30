#include "idleizer.h"

void runGame(int game_width, int game_height, char* title) {
  setGameSize(game_width, game_height);
  //
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  SetTargetFPS(60);

	// Create the window and OpenGL context
	InitWindow(game_width, game_height, title);
	SearchAndSetResourceDir("resources");

  char currency_amount_text[100];
  int mouseBtn = -1;
  // game loop
	while (!WindowShouldClose()) {
    // controls
    mouseButtonsHandler(BUTTONS, BUTTONS_COUNT, &mouseBtn);
    // drawing
		BeginDrawing();
		ClearBackground(WHITE);

    drawSections(SECTIONS, SECTIONS_COUNT);
    drawLabels(LABELS, LABELS_COUNT);
    drawCurrencies(CURRENCIES, CURRENCIES_COUNT);
    drawButtons(BUTTONS, BUTTONS_COUNT);
   
    // handles the logic for and draws tickers
    handleTickers(TICKERS, TICKERS_COUNT);
		
		EndDrawing();
	}
  
	CloseWindow();
}

void initCore(Core* core) {
  GAME_CORE = core;
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

void setupSections(Section* sections, int count) {
  SECTIONS = sections;
  SECTIONS_COUNT = count;
}

void destroyCore(Core* core) {
  free(core->sections);
  free(core->currencies);
  free(core->buttons);
  free(core->labels);
  free(core->tickers);
}

void setTextBuffer(TextBuffer* buffer, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer->text, fmt, args);
  va_end(args);
}
