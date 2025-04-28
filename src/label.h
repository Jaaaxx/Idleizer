#ifndef LABEL_H
#define LABEL_H
#include <stdbool.h>
#include "vr_vec.h"

typedef struct {
  char* text;
  VrVec pos;
  int fontSize;
  Color color;
  bool hidden;
  Section* sec;
} Label;
#endif
