#include <stdio.h>
#include "section.h"
#include "core.h"
#include <stdlib.h>

float getSecWidth(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 1;
  }
  if (sec->parent == -1) {
    // equivalent to GAME_WIDTH
    return sec->rec.w;
  }

  return (sec->rec.w / 100) * getSecWidth(core, &secs[sec->parent]);
}

float getSecHeight(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 1;
  }
   if (sec->parent == -1) {
    // equivalent to GAME_HEIGHT
    return sec->rec.h;
  }

  return (sec->rec.h / 100) * getSecHeight(core, &secs[sec->parent]);
}
float getSecX(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 0;
  }
  if (sec->parent == -1) {
    return sec->rec.x;
  }

  return (sec->rec.x / 100) * getSecWidth(core, &secs[sec->parent]) + getSecX(core, &secs[sec->parent]);
}

float getSecY(Core* core, Section* sec) {
  Section* secs = core->sections;
  if (sec == 0) {
    return 0;
  }
  if (sec->parent == -1) {
    return sec->rec.y;
  }

  return (sec->rec.y / 100) * getSecHeight(core, &secs[sec->parent]) + getSecY(core, &secs[sec->parent]);
}


void addSections(Core* core, const VrRec* rects, const Color* colors, 
                           const int* parent_indices, const bool* hiddens, int count) {
  if (&core->sections == NULL) {
    core->sections_size = 0;
  }
  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + count));
  for (int i = 0; i < count; i++) {
    core->sections[i+core->sections_size].rec = rects[i];
    core->sections[i+core->sections_size].bg = colors[i];
    core->sections[i+core->sections_size].parent = parent_indices[i];
    core->sections[i+core->sections_size].hidden = hiddens[i];
  }
  core->sections_size += count;
}

int addSection(Core* core, const VrRec rect, const Color color, const bool hidden, int parent) {
  if (&core->sections == NULL) {
    core->sections_size = 0;
  }
  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + 1));

  Section* s = &core->sections[core->sections_size];
  s->rec = rect;
  s->bg = color;
  s->parent = parent;
  s->hidden = hidden;

  return core->sections_size++;
}

