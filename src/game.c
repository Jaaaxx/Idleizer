#include "game.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define CLICK_CURSOR MOUSE_CURSOR_ARROW

typedef struct MouseEventListener {
  int mouseButton;
  int mouseEvent;
  void (*callback)(void*);
  void* ctx;
  bool persistent;
  bool active;
} MouseEventListener;

static int mouseCursor;
static MouseEventListener* listeners;
static int listenersSize = 0;

void shutdownMouseEventListeners() {
  for (int i = 0; i < listenersSize; i++) {
   if (listeners[i].ctx) {
     listeners[i].ctx = NULL;
   }
  }
  free(listeners);
  listeners = NULL;
  listenersSize = 0;
}

int addMouseEventListener(int id, int m_b, int m_e, void (*callback)(void*), void* ctx, bool persistent) {
  if (id == -1) {
    listeners = realloc(listeners, sizeof(MouseEventListener) * (listenersSize+1));
    listeners[listenersSize] = (MouseEventListener) { m_b, m_e, callback, ctx, persistent, true, false };
    return listenersSize++;
  } else {
    listeners[id] = (MouseEventListener) { m_b, m_e, callback, ctx, persistent, true, false };
    return id;
  }
}

static void handleMouseEventListeners() {
  for (int i = 0; i < listenersSize; i++) {
    MouseEventListener ln = listeners[i];
    if (ln.active) {
      if (ln.mouseEvent == MOUSE_EVENT_DOWN) {
        if (IsMouseButtonDown(ln.mouseButton)) {
          ln.callback(ln.ctx);
          listeners[i].active = ln.persistent;
        }
      } else if (ln.mouseEvent == MOUSE_EVENT_RELEASE) {
        if (!IsMouseButtonDown(ln.mouseButton)) {
          ln.callback(ln.ctx);
          listeners[i].active = ln.persistent;
        }
      }
    }
  }
}

void mouseButtonsHandler(Core* core, int* mouseBtn) {
  handleMouseEventListeners();

  mouseCursor = mouseCursor == CLICK_CURSOR ? mouseCursor : MOUSE_CURSOR_DEFAULT;
  if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    *mouseBtn = -1;
    mouseCursor = MOUSE_CURSOR_DEFAULT;
  }
  for (int i = 0; i < core->buttons_size; i++) {
    Button* b = &core->buttons[i];
    if (b->hidden || sectionHidden(core, b->sec)) continue;
    Rectangle rec = getTrueRec(core, b->rec, getSection(core, b->sec));
    bool mouseInRec = CheckCollisionPointRec(GetMousePosition(), rec);
    bool wasHovered = b->_hovered;
    b->_hovered = false;

    if (wasHovered && !mouseInRec) {
      b->hoverHandler(HOVER_EXIT, b->hoverCtx);
    }

    if (mouseInRec) {
      mouseCursor = mouseCursor == CLICK_CURSOR ? mouseCursor : MOUSE_CURSOR_POINTING_HAND;
      b->_hovered = true;
      if (!wasHovered) {
        b->hoverHandler(HOVER_ENTER, b->hoverCtx);
      }
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && *mouseBtn != 1) {
        if (b->handler) {
          b->handler(b->ctx);
        }
        *mouseBtn = 1;
        mouseCursor = CLICK_CURSOR;
      }
    }
  }
  SetMouseCursor(mouseCursor);
}

