#ifndef LABEL_H
#define LABEL_H
#include <stdbool.h>
#include "vr_vec.h"
#include <stdlib.h>

typedef struct Core Core;


typedef struct {
  char* text;
  VrVec pos;
  int fontSize;
  Color color;
  bool hidden;
  int sec;
} Label;


int addLabels(Core* core, Label* labels, int count);
int addLabel(Core* core, Label label);

#endif
