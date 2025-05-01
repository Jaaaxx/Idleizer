#include <stdio.h>
#include "section.h"
#include "core.h"

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
