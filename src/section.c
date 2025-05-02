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

// todo for this and all data types: improve defaults by giving users a createSection() function?
// it would populate with sentinel values to determine what the user actually set and improve defaults
// could be more trouble for the user though adding complexity per object created
static void setDefaultSection(Section section, Section* ptr) {
  ptr->rec = section.rec;
  ptr->bg = section.bg;
  ptr->parent = section.parent >= 0 ? section.parent : -1;
  ptr->hidden = section.hidden;
}

int addSections(Core* core, Section* sections, int count) {
  if (core->sections == NULL) {
    core->sections_size = 0;
  }

  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + count));
  for (int i = 0; i < count; i++) {
    setDefaultSection(sections[i], &core->sections[i+core->sections_size]);
  }

  int index = core->sections_size;
  core->sections_size += count;
  return index;
}

int addSection(Core* core, Section section) {
  if (core->sections == NULL) {
    core->sections_size = 0;
  }

  core->sections = realloc(core->sections, sizeof(Section) * (core->sections_size + 1));
  setDefaultSection(section, &core->sections[core->sections_size]);

  return core->sections_size++;
}

