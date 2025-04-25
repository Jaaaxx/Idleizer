#ifndef BUTTON_H
#define BUTTON_H

typedef struct {
  Rectangle* rect;
  void (*func)();
} Button;

#endif
