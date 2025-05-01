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


void addLabels(Core* core, char** texts, VrVec* vecs, Color* colors, bool* hiddens, int* parents, int count);
int addLabel(Core* core, char* text, VrVec pos, Color color, bool hidden, int parent);

#endif
