#include "button.h"
#include "core.h"
#include "util.h"
#include <stddef.h>
#include "external/resource_loader.h"
#include <stdio.h>

void drawButtons(Core* core) {
  for (int i = 0; i < core->buttons_size; i++) {
    Button* b = &core->buttons[i];
    Label* l = &b->label;
    LOAD_FONT(l);
    if (!b->hidden && !sectionHidden(core, b->sec)) {
      Rectangle rec = getTrueRec(core, b->rec, getSection(core, b->sec));
      if (b->image.data != NULL) {
        if (b->_texture.id <= 0) {
          b->_texture = LoadTextureFromImage(b->image);
        }
        DrawTextureCentered(b->_texture, rec);
      } else {
        DrawRectangleRec(rec, Fade(LIGHTGRAY, 0.3f));
        DrawRectangleRoundedLinesEx(rec, 0.0f, 0.0f, 1.0f, Fade(BLACK, 0.4f));
        Rectangle lrec = getTrueRec(core, l->pos, getSection(core, l->sec));
        DrawTextEx(l->_font, l->text, (Vector2) {lrec.x, lrec.y}, l->fontSize, 0, l->color);
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
  ptr->label = button.label;
  ptr->label.text = button.label.text != NULL ? button.label.text : ptr->text;
  ptr->label.color = button.label.color.r != 0 || button.label.color.g != 0 ||
                        button.label.color.b != 0 ? button.label.color : BLACK;
  ptr->label.font = button.label.font != NULL ? button.label.font : getDefaultFontResource();
  ptr->label.fontSize = button.label.fontSize != 0 ? button.label.fontSize : 20;
  ptr->label.pos = button.label.pos.x != 0 || button.label.pos.y != 0 ? button.label.pos :
                                                          (VrRec) {ptr->rec.x+1, ptr->rec.y};
  ptr->label.sec = button.label.sec != 0 ? button.label.sec : ptr->sec;
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

    UNLOAD_FONT(&button->label);
  }
}

