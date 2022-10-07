#ifndef MOON_ENGINE_RENDERING_H
#define MOON_ENGINE_RENDERING_H

#include "Include.h"
#include "Camera.h"

// Clears a renderer
void Clear(SDL_Colour colour, SDL_Renderer* renderer);

// Draws a rectangle
void DrawRect(Rectangle rect, SDL_Colour colour, SDL_Renderer* renderer);

// Draws a rectangle in a camera
void DrawRectMod(Rectangle rect, Camera* camera, SDL_Colour colour, SDL_Renderer* renderer);

// Draws rectangle lines
void DrawRectLines(Rectangle rect, SDL_Colour colour, SDL_Renderer* renderer);

// Draws rectangle lines in a camera
void DrawRectLinesMod(Rectangle rect, Camera* camera, SDL_Colour colour, SDL_Renderer* renderer);

// Draws a line
void DrawLine(Line line, SDL_Renderer* renderer);

// Draws a triangle
void DrawTriangle(Tri* tri, SDL_Renderer* renderer);

// Draws a point
void DrawPoint(Vec2 point, SDL_Renderer* renderer);

// Draws a point in a camera
void DrawPointMod(Vec2 point, Camera* camera, SDL_Renderer* renderer);

// Renders texture
void DrawTexture(Bitmap tex, Rectangle *srcRect, Rectangle *dstRect, SDL_Renderer* renderer);

// Renders texture (extended parameters)
void DrawTextureEx(Bitmap tex, Rectangle *srcRect, Rectangle *dstRect, double rotAngle, SDL_Point *centre, SDL_RendererFlip flip, SDL_Renderer* renderer);

// Renders the backbuffer into the frontbuffer
void RenderBuffer(SDL_Renderer* renderer);

// Set target for rendering textures on
void SetRenderTarget(Bitmap renderTarget, SDL_Renderer* renderer);

// Set a blending mode (for shapes)
void SetBlendMode(SDL_BlendMode blendMode, SDL_Renderer* renderer);

// Sets a texture colour (for rendering)
void SetTextureColour(Bitmap tex, SDL_Colour colour, SDL_Renderer* renderer);

#endif