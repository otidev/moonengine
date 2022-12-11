#ifndef MOON_ENGINE_TEXTURE_H
#define MOON_ENGINE_TEXTURE_H

#include "Include.h"
#include "Window.h"

// Loads a texture from a file
Bitmap LoadTexture(char* filename);

// Creates a texture from scratch.
Bitmap CreateTexture(int width, int height);

// Creates a render target.
Bitmap CreateRenderTarget(int width, int height);

// Destroys (frees) a render target.
void DestroyRenderTarget(Bitmap* bitmap);

// Creates a texture from a surface.
Bitmap CreateTextureFromSurface(SDL_Surface* surf);

// Destroys all textures in the texture array.
void FreeTexArray(Bitmap *arrayPtr[], int size);

#endif