#ifndef LABEL_H
#define LABEL_H
#include <stdbool.h>
#include "vr_rec.h"
#include <stdlib.h>

typedef struct Core Core;


typedef struct {
  char* text;
  VrRec pos;
  int fontSize;
  Color color;
  bool hidden;
  int sec;
  char* font;
  Font _font;
} Label;


int addLabels(Core* core, Label* labels, int count);
int addLabel(Core* core, Label label);
void drawLabels(Core* core);
void unloadLabelResources(Core* core);

#endif
