#include "draw.h"
#include "raylib.h"

// draws the section outlines (borders and backgrounds) for different areas of the screen
void drawSectionOutlines(int game_width, int game_height) {
    int screenCenterX = game_width / 2;
    int menuBottom = game_height / 9;
    DrawLine(screenCenterX, menuBottom, screenCenterX, game_height, BLACK);
    DrawLine(0, menuBottom, game_width, menuBottom, BLACK);
}

// draws a button on the screen 
void drawButton(const Button* b) {
  DrawRectangleRec(*b->rect, Fade(LIGHTGRAY, 0.3f));
  DrawRectangleRoundedLinesEx(*b->rect, 0.0f, 0.0f, 1.0f, Fade(BLACK, 0.4f));
  DrawText(b->text, b->rect->x + 5, b->rect->y, 20, RED);

}

