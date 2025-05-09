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

// Unload texture loaded with LoadResourceTexture
void UnloadResourceTexture(Texture2D texture) {
    UnloadTexture(texture);
}

// Load image from file with automatic path resolution
Image LoadResourceImage(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadImage(path);
}

// Unload image loaded with LoadResourceImage
void UnloadResourceImage(Image image) {
    UnloadImage(image);
}

// Load font from file with automatic path resolution
Font LoadResourceFont(const char* fileName) {
  const char* path = GetResourcePath(fileName);
  Font f = LoadFont(path);
  SetTextureFilter(f.texture, TEXTURE_FILTER_BILINEAR);
  return f;
}

// Unload font loaded with LoadResourceFont
void UnloadResourceFont(Font* font) {
    if (font && font->glyphCount > 0) {
        UnloadFont(*font);
        *font = (Font){0}; // Reset to empty font
    }
}

// Load sound from file with automatic path resolution
Sound LoadResourceSound(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadSound(path);
}

// Unload sound loaded with LoadResourceSound
void UnloadResourceSound(Sound sound) {
    UnloadSound(sound);
}

// Load music stream from file with automatic path resolution
Music LoadResourceMusic(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadMusicStream(path);
}

// Unload music loaded with LoadResourceMusic
void UnloadResourceMusic(Music music) {
    UnloadMusicStream(music);
}

// Load shader from files with automatic path resolution
Shader LoadResourceShader(const char* vsFileName, const char* fsFileName) {
    const char* vsPath = vsFileName ? GetResourcePath(vsFileName) : NULL;
    const char* fsPath = fsFileName ? GetResourcePath(fsFileName) : NULL;
    return LoadShader(vsPath, fsPath);
}

// Unload shader loaded with LoadResourceShader
void UnloadResourceShader(Shader shader) {
    UnloadShader(shader);
}

// Load model from file with automatic path resolution
Model LoadResourceModel(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadModel(path);
}

// Unload model loaded with LoadResourceModel
void UnloadResourceModel(Model model) {
    UnloadModel(model);
}

// Load model animations from file with automatic path resolution
ModelAnimation* LoadResourceModelAnimations(const char* fileName, int* animCount) {
    const char* path = GetResourcePath(fileName);
    return LoadModelAnimations(path, animCount);
}

// Unload model animations loaded with LoadResourceModelAnimations
void UnloadResourceModelAnimations(ModelAnimation* animations, int animCount) {
    UnloadModelAnimations(animations, animCount);
}

// Load file text with automatic path resolution
char* LoadResourceFileText(const char* fileName) {
    const char* path = GetResourcePath(fileName);
    return LoadFileText(path);
}

// Unload file text loaded with LoadResourceFileText
void UnloadResourceFileText(char* text) {
    if (text) {
        UnloadFileText(text);
    }
} 
