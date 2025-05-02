#include "game.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void mouseButtonsHandler(Core* core, int* mouseBtn) {
  for (int i = 0; i < core->buttons_size; i++) {
    Button* b = &core->buttons[i];
    Rectangle rec = getTrueRec(core, b->rec, getSection(core, b->sec));
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        if (b->handler) {
          b->handler(b->ctx);
        }
        *mouseBtn = 1;
      } else if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *mouseBtn = -1;
      }
    }
  }
}

