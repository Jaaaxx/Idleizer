#include "section.h"
#include <stdio.h>

float getSecWidth(Section* sec) {
  if (sec == 0) {
    return 1;
  }
  if (sec->parent == 0) {
    // equivalent to GAME_WIDTH
    return sec->rec.w;
  }

  return (sec->rec.w / 100) * getSecWidth(sec->parent);
}

float getSecHeight(Section* sec) {
  if (sec == 0) {
    return 1;
  }
   if (sec->parent == 0) {
    // equivalent to GAME_HEIGHT
    return sec->rec.h;
  }

  return (sec->rec.h / 100) * getSecHeight(sec->parent);
}
float getSecX(Section* sec) {
  if (sec == 0) {
    return 0;
  }
  if (sec->parent == 0) {
    return sec->rec.x;
  }

  return (sec->rec.x / 100) * getSecWidth(sec->parent) + getSecX(sec->parent);
}

float getSecY(Section* sec) {
  if (sec == 0) {
    return 0;
  }
  if (sec->parent == 0) {
    return sec->rec.y;
  }

  return (sec->rec.y / 100) * getSecHeight(sec->parent) + getSecY(sec->parent);
}
