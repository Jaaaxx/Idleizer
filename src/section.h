#ifndef SECTION_H
#define SECTION_H
#include "raylib.h"
#include "vr_rec.h"
#include <stdbool.h>

typedef struct Core Core;

typedef struct Section {
  VrRec rec;
  Color bg;
  int parent;
  bool hidden;
} Section;

float getSecWidth(Core* core, Section* sec);
float getSecX(Core* core, Section* sec);
float getSecHeight(Core* core, Section* sec);
float getSecY(Core* core, Section* sec);

void addSections(Core* core, const VrRec* rects, const Color* colors, const int* parent_indices, const bool* hiddens, int count);
int addSection(Core* core, const VrRec rect, const Color color, const bool hidden, int parent);

#endif
