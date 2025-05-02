#include "button.h"
#include "core.h"
#include "util.h"
#include <stddef.h>

void drawButtons(Core* core) {
  for (int i = 0; i < core->buttons_size; i++) {
    Button* b = &core->buttons[i];
    if (!b->hidden && !getSection(core, b->sec)->hidden) {
      Rectangle rec = getTrueRec(core, b->rec, getSection(core, b->sec));
      if (b->image.data != NULL) {
        if (b->_texture.id <= 0) {
          b->_texture = LoadTextureFromImage(b->image);
        }
        DrawTextureCentered(b->_texture, rec);
      } else {
        DrawRectangleRec(rec, Fade(LIGHTGRAY, 0.3f));
        DrawRectangleRoundedLinesEx(rec, 0.0f, 0.0f, 1.0f, Fade(BLACK, 0.4f));
        DrawText(b->text, rec.x + 5, rec.y, 20, RED);
      }
    }
  }
}

static void setDefaultButton(Button button, Button* ptr) {
  ptr->text = button.text ? button.text : "default text";
  ptr->rec = button.rec;
  ptr->handler = button.handler ? button.handler : NULL;
  ptr->ctx = button.ctx ? button.ctx : NULL;
  ptr->hidden = button.hidden;
  ptr->sec = button.sec >= 0 ? button.sec : -1;
  ptr->image = button.image;
  ptr->_texture = button._texture;
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

void unloadButtonResources(Core* core) {
  for (int i = 0; i < core->buttons_size; i++) {
    Button* button = &core->buttons[i];
    
    if (button->_texture.id > 0) {
      UnloadTexture(button->_texture);
      button->_texture.id = 0;
    }
    
    if (button->image.data != NULL) {
      UnloadImage(button->image);
      button->image.data = NULL;
    }
  }
}

