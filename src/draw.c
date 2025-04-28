#include "draw.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

// draws the section outlines (borders and backgrounds) for different areas of the screen
void drawSectionOutlines(const int game_width, const int game_height) {
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

void drawCurrencies(Currency* currencies, const int currencies_count) {
  for (int i = 0; i < currencies_count; i++) {
    int arrSize = sizeof(currencies[i].name) + sizeof(char) * 30;
    char* currency_amount_text = malloc(arrSize);
    sprintf(currency_amount_text, "%s: %llu", currencies[i].name, currencies[i].amount);
    DrawText(currency_amount_text, currencies[i].pos.x, currencies[i].pos.y, 20, RED);
    currency_amount_text = calloc(arrSize, sizeof(char));
  }
}

void drawTicker(Ticker ticker, Color color) {
  int arrSize = sizeof(ticker.name) + sizeof(char) * 30;
  char* ticker_amount_text = malloc(arrSize);
  sprintf(ticker_amount_text, "%s: %d/%d", ticker.name, ticker.tick, ticker.frequency);
  DrawText(ticker_amount_text, ticker.pos.x, ticker.pos.y, 20, color);
  ticker_amount_text = calloc(arrSize, sizeof(char));
}

void drawLabels(Label* labels, const int labels_count) {
  for (int i = 0; i < labels_count; i++) {
    if (!labels[i].hidden)
      DrawText(labels[i].text, labels[i].pos.x, labels[i].pos.y, labels[i].fontSize, labels[i].color);
  }
}
