#include "vr_vec.h"
#include "section.h"
#include <stdlib.h>

Vector2* getTrueVec(VrVec vr_vec, Section* sec) {
  Vector2* ret = malloc(sizeof(Vector2));
  float sec_width = getSecWidth(sec);
  float sec_height = getSecHeight(sec);

  ret->x = getSecX(sec) + (vr_vec.x / 100 * sec_width);
  ret->y = getSecY(sec) + (vr_vec.y / 100 * sec_height);

  return ret;
}
