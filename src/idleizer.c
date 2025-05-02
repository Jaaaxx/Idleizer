#include "idleizer.h"

void runGame(Core* core, int game_width, int game_height, char* title) {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  SetTargetFPS(60);

	// Create the window and OpenGL context
	InitWindow(game_width, game_height, title);
	SearchAndSetResourceDir("resources");

  int mouseBtn = -1;
  // game loop
	while (!WindowShouldClose()) {
    // controls
    mouseButtonsHandler(core, &mouseBtn);
    // drawing
		BeginDrawing();
		ClearBackground(WHITE);

    drawSections(core);
    drawLabels(core);
    drawButtons(core);
  
    // tick handlers
    handleTickers(core);
	  handleCurrencies(core);

		EndDrawing();
	}
  
	CloseWindow();
}

static void destroyCore(Core* core) {
  free(core->sections);
  free(core->currencies);
  free(core->buttons);
  free(core->labels);
  free(core->tickers);
}

void freeAll(Core* core) {
  freeAllBuildings(core);
  destroyCore(core);
  printf("Freed all engine memory\n");
}

