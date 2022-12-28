#ifndef MOON_ENGINE_RENDERING_H
#define MOON_ENGINE_RENDERING_H

#include "Include.h"
#include "Camera.h"

// Clears a renderer
void Clear(SDL_Colour colour);

// Draws a rounded rectangle
void DrawRectR(Rectangle rect, float radius, SDL_Colour colour);

// Draws a rounded rectangle in a camera
void DrawRectRMod(Rectangle rect, float radius, Camera* camera, SDL_Colour colour);

// Draws a rectangle
void DrawRect(Rectangle rect, SDL_Colour colour);

// Draws a rectangle in a camera
void DrawRectMod(Rectangle rect, Camera* camera, SDL_Colour colour);

// Draws rounded rectangle lines
void DrawRectLinesR(Rectangle rect, float radius, SDL_Colour colour);

// Draws rounded rectangle lines in a camera
void DrawRectLinesRMod(Rectangle rect, float radius, Camera* camera, SDL_Colour colour);

// Draws rectangle lines
void DrawRectLines(Rectangle rect, SDL_Colour colour);

// Draws rectangle lines in a camera
void DrawRectLinesMod(Rectangle rect, Camera* camera, SDL_Colour colour);

// Draws a line
void DrawLine(Line line, SDL_Colour colour);

// Draws a triangle
void DrawTriangle(Tri* tri, SDL_Colour colour);

// Draws a point
void DrawPoint(Vec2 point, SDL_Colour colour);

// Draws a point in a camera
void DrawPointMod(Vec2 point, SDL_Colour colour, Camera* camera);

// Renders texture
void DrawTexture(Bitmap* image, Rectangle* srcRect, Rectangle* dstRect);

// Renders texture (extended parameters)
void DrawTextureEx(Bitmap* image, Rectangle* srcRect, Rectangle* dstRect, double rotAngle, Vec2* centre, SDL_RendererFlip flip);

// Renders the backbuffer into the frontbuffer
void RenderBuffer();

// Set target for rendering textures on
void SetRenderTarget(Bitmap* renderTarget);

// Set a blending mode (for shapes)
void SetBlendMode(GPU_BlendPresetEnum blendMode);

#endif