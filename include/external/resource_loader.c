#include "external/resource_loader.h"
#include "external/resource_path.h"
#include "raylib.h"

static char* DEFAULT_FONT = "fonts/Lato-Regular.ttf";

void setDefaultFontResource(char* resource) {
  DEFAULT_FONT = resource;
}

char* getDefaultFontResource() {
  return DEFAULT_FONT;
}

// Load texture from file with automatic path resolution
Texture2D LoadResourceTexture(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadTexture(path);
}

// Load image from file with automatic path resolution
Image LoadResourceImage(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadImage(path);
}

// Load font from file with automatic path resolution
Font LoadResourceFont(const char* fileName) {
  const char* path = GetResourcePath(fileName);
  Font f = LoadFont(path);
  SetTextureFilter(f.texture, TEXTURE_FILTER_BILINEAR);
  return f;
}

// Load sound from file with automatic path resolution
Sound LoadResourceSound(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadSound(path);
}

// Load music stream from file with automatic path resolution
Music LoadResourceMusic(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadMusicStream(path);
}

// Load shader from files with automatic path resolution
Shader LoadResourceShader(const char* vsFileName, const char* fsFileName) {
    const char* vsPath = vsFileName ? GetResourcePath(vsFileName) : NULL;
    const char* fsPath = fsFileName ? GetResourcePath(fsFileName) : NULL;
    return LoadShader(vsPath, fsPath);
}

// Load model from file with automatic path resolution
Model LoadResourceModel(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadModel(path);
}

// Load model animations from file with automatic path resolution
ModelAnimation* LoadResourceModelAnimations(const char* fileName, int* animCount) {
    const char* path = GetResourcePath(fileName);
    return LoadModelAnimations(path, animCount);
}

// Load file text with automatic path resolution
char* LoadResourceFileText(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadFileText(path);
} 
