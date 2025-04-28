#include "vr_rec.h"
#include "section.h"
#include <stdlib.h>
#include <stdio.h>

Rectangle* getSectionRec(Section* sec) {
  Rectangle* ret = malloc(sizeof(Rectangle));
  float sec_width = getSecWidth(sec);
  float sec_height = getSecHeight(sec);

  ret->x = getSecX(sec);
  ret->y = getSecY(sec);
  ret->width = sec_width;
  ret->height = sec_height;
  return ret;
}

Rectangle* getTrueRec(VrRec vr_rec, Section* sec) {
  Rectangle* ret = malloc(sizeof(Rectangle));
  float sec_width = getSecWidth(sec);
  float sec_height = getSecHeight(sec);

  ret->x = getSecX(sec) + (vr_rec.x / 100 * sec_width);
  ret->y = getSecY(sec) + (vr_rec.y / 100 * sec_height);
  ret->width = (vr_rec.w / 100) * sec_width;
  ret->height = (vr_rec.h / 100) * sec_height;
  return ret;
}
