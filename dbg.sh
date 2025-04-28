clear
gcc -g \
  -Ibuild/external/raylib-master/src \
  -Iinclude \
  -Isrc \
  -Lbuild/external/raylib-master/src \
  -o bin/game \
  src/*.c \
  -lraylib -lm -ldl -lpthread -lGL
gdb ./bin/game
