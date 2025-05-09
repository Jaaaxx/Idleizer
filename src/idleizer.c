#include "idleizer.h"

void runGame(Core* core, int game_width, int game_height, char* title) {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  SetTargetFPS(60);

	// Create the window and OpenGL context
	InitWindow(game_width, game_height, title);

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

  CloseResourcePaths();
  freeAll(core);
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
  // First unload all resources
  unloadButtonResources(core);
  unloadLabelResources(core);
  unloadCurrencyResources(core);
  unloadTickerResources(core);
  unloadBuildingResources(core);
  
  // Then free all allocated memory
  freeAllBuildings(core);
  cleanupCpsResources();
  shutdownMouseEventListeners();
  cleanupSectionHideResources();
  freeCurrencyContexts();
  
  // Finally destroy the core structure
  destroyCore(core);
  printf("Freed all engine memory\n");
}

