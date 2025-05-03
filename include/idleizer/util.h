#ifndef UTIL_H
#define UTIL_H
#include <stdbool.h>
#include "raylib.h"

typedef struct BoolArr {
  bool* arr;
  int size;
} BoolArr;

typedef struct Core Core;

bool ColorsEqual(Color c1, Color c2);
double calculateCPS(Core* core, int idx);
void cleanupCpsResources(void);
void DrawTextureCentered(Texture2D texture, Rectangle container);
#endif
