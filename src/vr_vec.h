#ifndef VR_VEC
#define VR_VEC
#include "raylib.h"

typedef struct Section Section;

typedef struct {
  float x;
  float y;
} VrVec;

Vector2* getTrueVec(VrVec vr_vec, Section* sec);
#endif
