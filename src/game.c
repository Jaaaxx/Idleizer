#include "game.h"

Currency* CURRENCIES = 0; 
int CURRENCIES_COUNT = 0; 

Button* BUTTONS = 0;
int BUTTONS_COUNT = 0;

void setupCurrencies(Currency* currencies, int count) {
  CURRENCIES = currencies;
  CURRENCIES_COUNT = count;
}

void setupButtons(Button* buttons, int count) {
  BUTTONS = buttons;
  BUTTONS_COUNT = count;
}

