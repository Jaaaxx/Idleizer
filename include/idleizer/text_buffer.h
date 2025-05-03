#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

typedef struct {
  char text[64];
} TextBuffer;

void setTextBuffer(TextBuffer* buffer, const char* fmt, ...);
#endif
