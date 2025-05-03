# Mine Hunter Example Makefile

# This Makefile is used for manual building without premake
# For normal use, please use the premake build system:
# 
#   cd ../../build
#   ./premake5 gmake2
#   cd ..
#   make config=debug_x64 MineHunter

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include -I../../include/idleizer
LDFLAGS = -L../../bin/Debug -lIdleizer -lraylib -lm -ldl -lpthread

# Target executable
TARGET = MineHunter

# Source files
SRCS = MineHunter.c

# Object files
OBJS = $(SRCS:.c=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 
