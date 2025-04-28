#ifndef LABEL_H
#define LABEL_H
#include <stdbool.h>

typedef struct {
  char* text;
  Vector2 pos;
  int fontSize;
  Color color;
  bool hidden;
} Label;
#endif
