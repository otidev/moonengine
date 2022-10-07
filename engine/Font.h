#ifndef MOON_ENGINE_FONT_H
#define MOON_ENGINE_FONT_H

#include "Include.h"
#include "Window.h"
#include "Texture.h"

// Initializes a font.
void InitFont(Font* font, char* filename, int fontSize);

// Loads a font texture for rendering.
void LoadFontTexture(Font* font, char* text, SDL_Colour colour);

// Loads a font texture for rendering (with text wraps).
void LoadFontTextureWrap(Font* font, char* text, int wrapWidth, SDL_Colour colour);

// Closes a font
void CloseFont(Font* font);

#endif