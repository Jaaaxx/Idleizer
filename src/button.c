#include "button.h"
#include "core.h"
#include <stddef.h>

void addButtons(Core* core, const char** texts, const VrRec* recs,
                   void (**handlers)(void *), void** ctxs, int* secs, bool* hiddens, int count) {
  if (&core->buttons == NULL) {
    core->buttons_size = 0;
  }
  Button* buttons = realloc(core->buttons, sizeof(Button) * (core->buttons_size + count));
  for (int i = 0; i < count; i++) {
    buttons[i+core->buttons_size].text = texts[i];
    buttons[i+core->buttons_size].rec = recs[i];
    buttons[i+core->buttons_size].handler = handlers[i];
    buttons[i+core->buttons_size].ctx = ctxs[i];
    buttons[i+core->buttons_size].hidden = hiddens[i];
    buttons[i+core->buttons_size].sec = secs[i];
  }
  core->buttons = buttons;
  core->buttons_size += count;
}

int addButton(Core* core, char* text, VrRec rec, void (*handler)(void*), void* ctx, bool hidden, int sec) {
  if (&core->buttons == NULL) {
    core->buttons_size = 0;
  }

  core->buttons = realloc(core->buttons, sizeof(Button) * (core->buttons_size + 1));

  Button* b = &core->buttons[core->buttons_size];
  b->text = text;
  b->rec = rec;
  b->handler = handler;
  b->ctx = ctx;
  b->hidden = hidden;
  b->sec = sec;

  return core->buttons_size++;
}

