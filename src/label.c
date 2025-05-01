#include "label.h"
#include "core.h"

void addLabels(Core* core, char** texts, VrVec* vecs, Color* colors,
                  bool* hiddens, int* parents, int count) {
  if (&core->labels == NULL) {
    core->labels_size = 0;
  }
  Label* labels = realloc(core->labels, sizeof(Label) * (core->labels_size + count));
  for (int i = 0; i < count; i++) {
    labels[i+core->labels_size].text = texts[i];
    labels[i+core->labels_size].pos = vecs[i];
    labels[i+core->labels_size].fontSize = 20;
    labels[i+core->labels_size].color = colors[i];
    labels[i+core->labels_size].hidden = hiddens[i];
    labels[i+core->labels_size].sec = parents[i];
  }
  core->labels = labels;
  core->labels_size += count;
}

int addLabel(Core* core, char* text, VrVec pos, Color color, bool hidden, int parent) {
  if (&core->labels == NULL) {
    core->labels_size = 0;
  }
  core->labels = realloc(core->labels, sizeof(Label) * (core->labels_size + 1));

  Label* l = &core->labels[core->labels_size];
  l->text = text;
  l->pos = pos;
  l->fontSize = 20;
  l->color = color;
  l->hidden = hidden;
  l->sec = parent;

  return core->labels_size++;
}

