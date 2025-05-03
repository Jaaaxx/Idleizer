// viewport-relative rect (floats from 0-100 as vh and vw)
#ifndef VR_REC_H
#define VR_REC_H
#include "raylib.h"

typedef struct Core Core;
typedef struct Section Section;

typedef struct {
  float x;
  float y;
  float w;
  float h;
} VrRec;

Rectangle getSectionRec(Core* core, Section* sec);
Rectangle getTrueRec(Core* core, VrRec vr_rec, Section* sec);
#endif
