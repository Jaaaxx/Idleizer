#include "draw.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

// draws the section outlines (borders and backgrounds) for different areas of the screen
void drawSectionOutlines(int game_width, int game_height) {
    int screenCenterX = game_width / 2;
    int menuBottom = game_height / 9;
    DrawLine(screenCenterX, menuBottom, screenCenterX, game_height, BLACK);
    DrawLine(0, menuBottom, game_width, menuBottom, BLACK);
}

// draws a button on the screen 
void drawButton(const Button* b) {
  DrawRectangleRec(*b->rec, Fade(LIGHTGRAY, 0.3f));
  DrawRectangleRoundedLinesEx(*b->rec, 0.0f, 0.0f, 1.0f, Fade(BLACK, 0.4f));
  DrawText(b->text, b->rec->x + 5, b->rec->y, 20, RED);
}

void drawButtons(const Button* buttons, const int buttons_count) {
  for (int i = 0; i < buttons_count; i++) {
    drawButton(&buttons[i]);
  }
}

void drawCurrencies(Currency* currencies, int currencies_count) {
  for (int i = 0; i < currencies_count; i++) {
    int arrSize = sizeof(currencies[i].name) + sizeof(char) * 30;
    char* currency_amount_text = malloc(arrSize);
    sprintf(currency_amount_text, "%s: %llu", currencies[i].name, currencies[i].amount);
    DrawText(currency_amount_text, currencies[i].pos.x, currencies[i].pos.y, 20, RED);
    currency_amount_text = calloc(arrSize, sizeof(char));
  }
}
