#ifndef MOON_ENGINE_SPRITE_H
#define MOON_ENGINE_SPRITE_H

#include "Window.h"
#include "Include.h"
#include "Texture.h"
#include "Camera.h"
#include "Rendering.h"

// Handles animation.
void PlayAnim(Sprite *spr, float updateTime);

// Renders a sprite onto the screen
void RenderSprite(Sprite *spr, SDL_Renderer* renderer);

// Renders a sprite onto the screen in a camera
void RenderSpriteMod(Sprite* spr, Camera* camera, SDL_Renderer* renderer);

// Sets up a sprite.
void InitSprite(Sprite *spr, int width, int height, char* textureFilename);

// Sets up a sprite without a source texture attached
void InitSpriteNoTex(Sprite *spr, int width, int height);

// Sets scale of sprite
void SetScale(Sprite* spr);

#endif