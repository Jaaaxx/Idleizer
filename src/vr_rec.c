#include "vr_rec.h"
#include "section.h"
#include "core.h"
#include <stdlib.h>
#include <stdio.h>

Rectangle getSectionRec(Core* core, Section* sec) {
  Rectangle ret;
  float sec_width = getSecWidth(core, sec);
  float sec_height = getSecHeight(core, sec);

  ret.x = getSecX(core, sec);
  ret.y = getSecY(core, sec);
  ret.width = sec_width;
  ret.height = sec_height;
  return ret;
}

Rectangle getTrueRec(Core* core, VrRec vr_rec, Section* sec) {
  Rectangle ret;
  float sec_width = getSecWidth(core, sec);
  float sec_height = getSecHeight(core, sec);

  ret.x = getSecX(core, sec) + (vr_rec.x / 100 * sec_width);
  ret.y = getSecY(core, sec) + (vr_rec.y / 100 * sec_height);
  ret.width = (vr_rec.w / 100) * sec_width;
  ret.height = (vr_rec.h / 100) * sec_height;
  return ret;
}
