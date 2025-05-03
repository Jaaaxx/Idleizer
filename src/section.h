#ifndef SECTION_H
#define SECTION_H
#include "raylib.h"
#include "vr_rec.h"
#include "util.h"
#include <stdbool.h>

typedef struct Core Core;

typedef struct Section {
  VrRec rec;
  Color bg;
  int parent;
  bool hidden;
} Section;

Section* getSection(Core* core, int idx);

void cleanupSectionHideResources();

float getSecWidth(Core* core, Section* sec);
float getSecX(Core* core, Section* sec);
float getSecHeight(Core* core, Section* sec);
float getSecY(Core* core, Section* sec);

void toggleSectionHide(Core* core, int section);
bool sectionHidden(Core* core, int section);

void drawSections(Core* core);
int addSections(Core* core, Section* sections, int count);
int addSection(Core* core, Section section); 

#endif
