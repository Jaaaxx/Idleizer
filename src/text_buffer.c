#include "text_buffer.h"
#include <stdarg.h>
#include <stdio.h>

void setTextBuffer(TextBuffer* buffer, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buffer->text, fmt, args);
  va_end(args);
}

