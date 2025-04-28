#include "handlers.h"

void mouseButtonsHandler(Button* buttons, int buttons_count, int* mouseBtn) {
  for (int i = 0; i < buttons_count; i++) {
    if (CheckCollisionPointRec(GetMousePosition(), *buttons[i].rec)) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        buttons[i].handler();
        *mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *mouseBtn = -1;
      }
    }
  }
}


