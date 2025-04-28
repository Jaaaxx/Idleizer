#ifndef SECTION_H
#define SECTION_H
#include "raylib.h"
#include "vr_rec.h"

typedef struct Section {
  VrRec rec;
  Color bg;
  Section* parent;
} Section;

float getSecWidth(Section* sec);
float getSecX(Section* sec);
float getSecHeight(Section* sec);
float getSecY(Section* sec);

#endif
