#ifndef TICKER_H
#define TICKER_H
typedef struct {
  char* name;
  int frequency;
  int tick;
  Vector2 pos;
  void (*handler)(); 
} Ticker;
#endif
