#include "vr_vec.h"
#include "core.h"
#include "section.h"
#include <stdlib.h>

Vector2 getTrueVec(Core* core, VrVec vr_vec, Section* sec) {
  Vector2 ret;
  float sec_width = getSecWidth(core, sec);
  float sec_height = getSecHeight(core, sec);

  ret.x = getSecX(core, sec) + (vr_vec.x / 100 * sec_width);
  ret.y = getSecY(core, sec) + (vr_vec.y / 100 * sec_height);

  return ret;
}
