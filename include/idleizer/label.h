#ifndef LABEL_H
#define LABEL_H
#include <stdbool.h>
#include "vr_vec.h"
#include <stdlib.h>

typedef struct Core Core;


typedef struct {
  char* text;
  // todo turn this into a rec and use it to calculate line breaks, font
  VrVec pos;
  int fontSize;
  Color color;
  bool hidden;
  // todo implement
  bool textCentered;
  int sec;
} Label;


int addLabels(Core* core, Label* labels, int count);
int addLabel(Core* core, Label label);
void drawLabels(Core* core);

#endif
