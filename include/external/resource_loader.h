#ifndef EXTERNAL_RESOURCE_LOADER_H
#define EXTERNAL_RESOURCE_LOADER_H

#include "raylib.h"

#define LOAD_FONT(obj)                                               \
    do {                                                             \
        if ((obj)->_font.glyphCount == 0) {                          \
            (obj)->_font = LoadResourceFont((obj)->font);           \
        }                                                            \
    } while (0)
// Load texture from file with automatic path resolution
// Searches in all registered resource directories
Texture2D LoadResourceTexture(const char* fileName);

// Load image from file with automatic path resolution
// Searches in all registered resource directories
Image LoadResourceImage(const char* fileName);

// Load font from file with automatic path resolution
// Searches in all registered resource directories
Font LoadResourceFont(const char* fileName);
char* getDefaultFontResource();

// Load sound from file with automatic path resolution
// Searches in all registered resource directories
Sound LoadResourceSound(const char* fileName);

// Load music stream from file with automatic path resolution
// Searches in all registered resource directories
Music LoadResourceMusic(const char* fileName);

// Load shader from files with automatic path resolution
// Searches in all registered resource directories
Shader LoadResourceShader(const char* vsFileName, const char* fsFileName);

// Load model from file with automatic path resolution
// Searches in all registered resource directories
Model LoadResourceModel(const char* fileName);

// Load model animations from file with automatic path resolution
// Searches in all registered resource directories
ModelAnimation* LoadResourceModelAnimations(const char* fileName, int* animCount);

// Load file text with automatic path resolution
// Searches in all registered resource directories
char* LoadResourceFileText(const char* fileName);

#endif // EXTERNAL_RESOURCE_LOADER_H 
