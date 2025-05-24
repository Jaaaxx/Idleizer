#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "raylib.h"
#include "currency.h"
#include "ticker.h"
#include "label.h"
#include "core.h"

typedef enum MOUSE_EVENT {
  MOUSE_EVENT_DOWN,
  MOUSE_EVENT_RELEASE,
} MOUSE_EVENT;

typedef enum HoverState {
  HOVER_ENTER,
  HOVER_EXIT
} HoverState;

void shutdownMouseEventListeners();
int addMouseEventListener(int id, int m_b, int m_e, void (*callback)(void*), void* ctx, bool persistent);
void mouseButtonsHandler(Core* core, int* mouseBtn);
#endif
