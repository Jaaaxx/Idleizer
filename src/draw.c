#include "draw.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool ColorsEqual(Color c1, Color c2) {
    return (c1.r == c2.r) &&
           (c1.g == c2.g) &&
           (c1.b == c2.b) &&
           (c1.a == c2.a);
}

void drawSections(Section* sections, int count) {
  for (int i = 0; i < count; i++) {
    Rectangle* rec = getSectionRec(&sections[i]);  
    DrawRectangleRec(*rec, sections[i].bg); 
    DrawRectangleLines(rec->x, rec->y, rec->width, rec->height, BLACK);
  }
}

void drawButtons(Button* buttons, const int buttons_count) {
  for (int i = 0; i < buttons_count; i++) {
    Rectangle* rec = getTrueRec(buttons[i].rec, buttons[i].sec);  
    DrawRectangleRec(*rec, Fade(LIGHTGRAY, 0.3f));
    DrawRectangleRoundedLinesEx(*rec, 0.0f, 0.0f, 1.0f, Fade(BLACK, 0.4f));
    DrawText(buttons[i].text, rec->x + 5, rec->y, 20, RED);
  }
}

void drawCurrencies(Currency* currencies, const int currencies_count) {
  for (int i = 0; i < currencies_count; i++) {
    Vector2* rec = getTrueVec(currencies[i].pos, currencies[i].sec);

    int arrSize = sizeof(currencies[i].name) + sizeof(char) * 30;
    char* currency_amount_text = malloc(arrSize);
    sprintf(currency_amount_text, "%s: %.0f", currencies[i].name, currencies[i].amount);
    DrawText(currency_amount_text, rec->x, rec->y, 20, RED);
    currency_amount_text = calloc(arrSize, sizeof(char));
  }
}

void drawTicker(Ticker ticker, Color color) {
  int nameLen = strlen(ticker.name);
  int arrSize = nameLen * 10;
  Vector2* vec = getTrueVec(ticker.pos, ticker.sec);
  char* ticker_amount_text = malloc(arrSize);
  sprintf(ticker_amount_text, "%s", ticker.name);
  for (int i = 0; i < ticker.displayTick; i++) {
    ticker_amount_text[nameLen+i] = '.';
  }
  ticker_amount_text[nameLen+ticker.displayTick] = '\0';
  DrawText(ticker_amount_text, vec->x, vec->y, 20, color);
  ticker_amount_text = calloc(arrSize, sizeof(char));
}

void drawLabels(Label* labels, const int labels_count) {
  for (int i = 0; i < labels_count; i++) {
    if (!labels[i].hidden) {
      Vector2* vec = getTrueVec(labels[i].pos, labels[i].sec);
      DrawText(labels[i].text, vec->x, vec->y, labels[i].fontSize, labels[i].color);
    }
  }
}
