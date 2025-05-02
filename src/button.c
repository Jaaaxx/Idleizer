#include "button.h"
#include "core.h"
#include <stddef.h>

static void setDefaultButton(Button button, Button* ptr) {
  ptr->text = button.text ? button.text : "default text";
  ptr->rec = button.rec;
  ptr->handler = button.handler ? button.handler : NULL;
  ptr->ctx = button.ctx ? button.ctx : NULL;
  ptr->hidden = button.hidden;
  ptr->sec = button.sec >= 0 ? button.sec : -1;
}

int addButtons(Core* core, Button* buttons, int count) {
  if (core->buttons == NULL) {
    core->buttons_size = 0;
  }

  core->buttons = realloc(core->buttons, sizeof(Button) * (core->buttons_size + count));
  for (int i = 0; i < count; i++) {
    setDefaultButton(buttons[i], &core->buttons[i+core->buttons_size]);
  }

  int index = core->buttons_size;
  core->buttons_size += count;
  return index;
}

int addButton(Core* core, Button button) {
  if (core->buttons == NULL) {
    core->buttons_size = 0;
  }

  core->buttons = realloc(core->buttons, sizeof(Button) * (core->buttons_size + 1));
  setDefaultButton(button, &core->buttons[core->buttons_size]); 

  return core->buttons_size++;
}

