#include "util.h"
#include "core.h"
#include <stdlib.h>
#include <stdbool.h>

static int currSize = -1;
static double* prevCurrs = NULL;

bool ColorsEqual(Color c1, Color c2) {
  return (c1.r == c2.r) &&
         (c1.g == c2.g) &&
         (c1.b == c2.b) &&
         (c1.a == c2.a);
}

double calculateCPS(Core* core, int idx) {
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

// Function to clean up the memory allocated in calculateCPS
void cleanupCpsResources() {
  if (prevCurrs != NULL) {
    free(prevCurrs);
    prevCurrs = NULL;
    currSize = -1;
  }
}

void DrawTextureCentered(Texture2D texture, Rectangle container) {
  float textureAspect = (float)texture.width / texture.height;
  float containerAspect = container.width / container.height;

  float scale;
  if (textureAspect > containerAspect) {
    // Texture is wider relative to container; fit width
    scale = container.width / texture.width;
  } else {
    // Texture is taller (or equal aspect); fit height
    scale = container.height / texture.height;
  }

  float destWidth  = texture.width * scale;
  float destHeight = texture.height * scale;
  float destX = container.x + (container.width  - destWidth)  / 2.0f;
  float destY = container.y + (container.height - destHeight) / 2.0f;

  Rectangle dest = { destX, destY, destWidth, destHeight };
  Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };

  DrawTexturePro(texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
}
