#include "util.h"

bool ColorsEqual(Color c1, Color c2) {
  return (c1.r == c2.r) &&
         (c1.g == c2.g) &&
         (c1.b == c2.b) &&
         (c1.a == c2.a);
}

double calculateCPS(Core* core, int idx) {
  static int currSize = -1;
  static double* prevCurrs = NULL;

  if (currSize != core->currencies_size) {
    currSize = core->currencies_size;
    if (prevCurrs == NULL) {
      prevCurrs = (double*) calloc(core->currencies_size, sizeof(double));
    } else {
      prevCurrs = (double*) realloc(prevCurrs, core->currencies_size * sizeof(double));
    }
  }
  
  int amt = core->currencies[idx].amount;
  double ret;
  if (amt >= prevCurrs[idx]) {
    ret = (core->currencies[idx].amount - prevCurrs[idx]);
  } else {
    ret = core->currencies[idx].cps;
  }
  prevCurrs[idx] = core->currencies[idx].amount;
  return ret; 
}

void DrawTextureCentered(Texture2D texture, Rectangle container) {
    float destX = container.x + (container.width  - texture.width)  / 2.0f;
    float destY = container.y + (container.height - texture.height) / 2.0f;

    DrawTexture(texture, (int)destX, (int)destY, WHITE);
}
