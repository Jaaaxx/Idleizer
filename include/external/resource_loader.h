#ifndef EXTERNAL_RESOURCE_LOADER_H
#define EXTERNAL_RESOURCE_LOADER_H

#include "raylib.h"

#define LOAD_FONT(obj)                                               \
    do {                                                             \
        if ((obj)->_font.glyphCount == 0) {                          \
            (obj)->_font = LoadResourceFont((obj)->font);           \
        }                                                            \
    } while (0)

#define UNLOAD_FONT(obj)                                             \
    do {                                                             \
        if ((obj)->_font.glyphCount > 0) {                           \
            UnloadResourceFont(&((obj)->_font));                     \
            (obj)->_font = (Font){0};                                \
        }                                                            \
    } while (0)

// Load texture from file with automatic path resolution
// Searches in all registered resource directories
Texture2D LoadResourceTexture(const char* fileName);

// Unload texture loaded with LoadResourceTexture
void UnloadResourceTexture(Texture2D texture);

// Load image from file with automatic path resolution
// Searches in all registered resource directories
Image LoadResourceImage(const char* fileName);

// Unload image loaded with LoadResourceImage
void UnloadResourceImage(Image image);

// Load font from file with automatic path resolution
// Searches in all registered resource directories
Font LoadResourceFont(const char* fileName);

// Unload font loaded with LoadResourceFont
void UnloadResourceFont(Font* font);

char* getDefaultFontResource();
void setDefaultFontResource(char* resource);

// Load sound from file with automatic path resolution
// Searches in all registered resource directories
Sound LoadResourceSound(const char* fileName);

// Unload sound loaded with LoadResourceSound
void UnloadResourceSound(Sound sound);

// Load music stream from file with automatic path resolution
// Searches in all registered resource directories
Music LoadResourceMusic(const char* fileName);

// Unload music loaded with LoadResourceMusic
void UnloadResourceMusic(Music music);

// Load shader from files with automatic path resolution
// Searches in all registered resource directories
Shader LoadResourceShader(const char* vsFileName, const char* fsFileName);

// Unload shader loaded with LoadResourceShader
void UnloadResourceShader(Shader shader);

// Load model from file with automatic path resolution
// Searches in all registered resource directories
Model LoadResourceModel(const char* fileName);

// Unload model loaded with LoadResourceModel
void UnloadResourceModel(Model model);

// Load model animations from file with automatic path resolution
// Searches in all registered resource directories
ModelAnimation* LoadResourceModelAnimations(const char* fileName, int* animCount);

// Unload model animations loaded with LoadResourceModelAnimations
void UnloadResourceModelAnimations(ModelAnimation* animations, int animCount);

// Load file text with automatic path resolution
// Searches in all registered resource directories
char* LoadResourceFileText(const char* fileName);

// Unload file text loaded with LoadResourceFileText
void UnloadResourceFileText(char* text);

#endif // EXTERNAL_RESOURCE_LOADER_H 
