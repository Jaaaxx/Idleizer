#ifndef UTIL_H
#define UTIL_H
#include "core.h"

bool ColorsEqual(Color c1, Color c2);
double calculateCPS(Core* core, int idx);
void DrawTextureCentered(Texture2D texture, Rectangle container);
#endif
