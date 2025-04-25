#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#ifndef CURRENCY_NAME
#define CURRENCY_NAME "Money"  
#endif

int main () {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Idleizer");
	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");
 
  const char* currency_text = CURRENCY_NAME; 
  const int text_width = MeasureText(currency_text, 20);
	
  // game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		DrawText(currency_text, 200, 200, 20, BLACK);
		DrawText(": 100", 200 + 10 + text_width, 200, 20, BLACK);

		DrawTexture(wabbit, 400, 200, WHITE);
		
		EndDrawing();
	}

	UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}
