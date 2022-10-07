#ifndef MOON_ENGINE_TEXTURE_H
#define MOON_ENGINE_TEXTURE_H

#include "Include.h"
#include "Window.h"

// Loads a texture from a file
Bitmap LoadTexture(char* filename);

// Loads a texture without a file
Bitmap CreateTexture(uint32_t byteFormat, int textureAccess, int width, int height);

// Creates a texture from a surface.
Bitmap CreateTextureFromSurface(SDL_Surface* surf);

// Destroys all textures in the texture array.
void FreeTexArray(Bitmap *arrayPtr[], int size);

#endif