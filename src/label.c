#include "label.h"
#include "core.h"
#include "external/text.h"
#include <stdio.h>

static void setDefaultLabel(Label label, Label* ptr) {
  ptr->text = label.text ? label.text : "default text";
  ptr->pos = label.pos;
  ptr->fontSize = label.fontSize > 0 ? label.fontSize : 20;
  ptr->color = label.color;
  ptr->hidden = label.hidden;
  ptr->sec = label.sec >= 0 ? label.sec : -1;
}

int addLabels(Core* core, Label* labels, int count) {
  if (core->labels == NULL) {
    core->labels_size = 0;
  }

  core->labels = realloc(core->labels, sizeof(Label) * (core->labels_size + count));
  for (int i = 0; i < count; i++) {
    setDefaultLabel(labels[i], &core->labels[i+core->labels_size]);
  }

  int index = core->labels_size;
  core->labels_size += count;
  return index;
}

int addLabel(Core* core, Label label) {
  if (core->labels == NULL) {
    core->labels_size = 0;
  }

  core->labels = realloc(core->labels, sizeof(Label) * (core->labels_size + 1));
  setDefaultLabel(label, &core->labels[core->labels_size]);

  return core->labels_size++;
}

void drawLabels(Core* core) {
  for (int i = 0; i < core->labels_size; i++) {
    const Label* l = &core->labels[i];
    if (!l->hidden && !sectionHidden(core, l->sec)) {
      Font font = GetFontDefault();
      Rectangle rec = getTrueRec(core, l->pos, getSection(core, l->sec));
      if (rec.width == 0 ) {
        DrawTextEx(font, l->text, (Vector2) {rec.x, rec.y}, l->fontSize, 1.0f, l->color);
      } else {
        DrawTextBoxed(font, l->text, rec, l->fontSize, 1.0f, true, l->color);
      }
    }
  }
}
