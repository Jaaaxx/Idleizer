#include "draw.h"
#include "raylib.h"

void drawSectionOutlines(int game_width, int game_height) {
    int screenCenterX = game_width / 2;
    int menuBottom = game_height / 9;
    DrawLine(screenCenterX, menuBottom, screenCenterX, game_height, BLACK);
    DrawLine(0, menuBottom, game_width, menuBottom, BLACK);
}

