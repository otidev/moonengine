#include "Rendering.h"

void Clear(SDL_Colour colour, SDL_Renderer* renderer) {
	// Put this in its own function
	char r, g, b, a;
	r = colour.r;
	g = colour.g;
	b = colour.b;
	a = colour.a;
	
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void DrawRect(Rectangle rect, SDL_Colour colour, SDL_Renderer* renderer) {
	// Get colour values.
	char r, g, b, a;
	r = colour.r;
	g = colour.g;
	b = colour.b;
	a = colour.a;

	// Set render colour, draw, then reset
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void DrawRectMod(Rectangle rect, Camera* camera, SDL_Colour colour, SDL_Renderer* renderer) {
	if (RectangleInCamera(camera, rect))
		DrawRect((Rectangle){rect.x - camera->rect.x, rect.y - camera->rect.y, rect.w, rect.h}, colour, renderer);
}

void DrawRectLines(Rectangle rect, SDL_Colour colour, SDL_Renderer* renderer) {
	char r, g, b, a;
	r = colour.r;
	g = colour.g;
	b = colour.b;
	a = colour.a;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void DrawRectLinesMod(Rectangle rect, Camera* camera, SDL_Colour colour, SDL_Renderer* renderer) {
	if (RectangleInCamera(camera, rect))
		DrawRectLines((Rectangle){rect.x - camera->rect.x, rect.y - camera->rect.y, rect.w, rect.h}, colour, renderer);
}

void DrawLine(Line line, SDL_Renderer* renderer) {
	SDL_RenderDrawLine(renderer, line.startPoint.x, line.startPoint.y, line.endPoint.x, line.endPoint.y);
}

void DrawTriangle(Tri* tri, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(renderer, tri->firstVert.x, tri->firstVert.y, tri->secondVert.x, tri->secondVert.y);
	SDL_RenderDrawLine(renderer, tri->secondVert.x, tri->secondVert.y, tri->thirdVert.x, tri->thirdVert.y);
	SDL_RenderDrawLine(renderer, tri->thirdVert.x, tri->thirdVert.y, tri->firstVert.x, tri->firstVert.y);
}

void DrawPoint(Vec2 point, SDL_Renderer* renderer) {
	SDL_RenderDrawPoint(renderer, point.x, point.y);
}

void DrawPointMod(Vec2 point, Camera* camera, SDL_Renderer* renderer) {
	if (PointInCamera(camera, point))
	DrawPoint((Vec2){point.x - camera->rect.x, point.y - camera->rect.y}, renderer);
}

void DrawTexture(SDL_Texture *tex, Rectangle *srcRect, Rectangle *dstRect, SDL_Renderer* renderer) {
	// If we can't render, something went wrong.
	if (SDL_RenderCopy(renderer, tex, srcRect, dstRect) != 0)
		fprintf(stderr, "\033[1mRendering error\033[0m: %s", SDL_GetError());
}

void DrawTextureEx(SDL_Texture *tex, Rectangle *srcRect, Rectangle *dstRect, double rotAngle, SDL_Point *centre, SDL_RendererFlip flip, SDL_Renderer* renderer) {
	if (SDL_RenderCopyEx(renderer, tex, srcRect, dstRect, rotAngle, centre, flip) != 0)
		fprintf(stderr, "\033[1mRendering error\033[0m: %s", SDL_GetError());
}

void RenderBuffer(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
}

void SetRenderTarget(SDL_Texture* renderTarget, SDL_Renderer* renderer) {
	SDL_SetRenderTarget(renderer, renderTarget);
}

void SetBlendMode(SDL_BlendMode blendMode, SDL_Renderer* renderer) {
	SDL_SetRenderDrawBlendMode(renderer, blendMode);
}

void SetTextureColour(SDL_Texture* tex, SDL_Colour colour, SDL_Renderer* renderer) {
	char r, g, b;
	r = colour.r;
	g = colour.g;
	b = colour.b;

	SDL_SetTextureColorMod(tex, r, g, b);
}