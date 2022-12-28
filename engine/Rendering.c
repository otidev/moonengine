#include "Rendering.h"

void Clear(SDL_Colour colour) {
	GPU_ClearColor(globalTarget, colour);
}

void DrawRectR(Rectangle rect, float radius, SDL_Colour colour) {
	GPU_RectangleRoundFilled2(globalTarget, rect, radius, colour);
}

void DrawRectRMod(Rectangle rect, float radius, Camera* camera, SDL_Colour colour) {
	if (RectangleInCamera(camera, rect))
		DrawRectR((Rectangle){rect.x - camera->rect.x, rect.y - camera->rect.y, rect.w, rect.h}, radius, colour);
}

void DrawRect(Rectangle rect, SDL_Colour colour) {
	GPU_RectangleFilled2(globalTarget, rect, colour);
}

void DrawRectMod(Rectangle rect, Camera* camera, SDL_Colour colour) {
	if (RectangleInCamera(camera, rect))
		DrawRect((Rectangle){rect.x - camera->rect.x, rect.y - camera->rect.y, rect.w, rect.h}, colour);
}

void DrawRectLinesR(Rectangle rect, float radius, SDL_Colour colour) {
	GPU_RectangleRound2(globalTarget, rect, radius, colour);
}

void DrawRectLinesRMod(Rectangle rect, float radius, Camera* camera, SDL_Colour colour) {
	if (RectangleInCamera(camera, rect))
		DrawRectLinesR((Rectangle){rect.x - camera->rect.x, rect.y - camera->rect.y, rect.w, rect.h}, radius, colour);
}

void DrawRectLines(Rectangle rect, SDL_Colour colour) {
	GPU_Rectangle2(globalTarget, rect, colour);
}

void DrawRectLinesMod(Rectangle rect, Camera* camera, SDL_Colour colour) {
	if (RectangleInCamera(camera, rect))
		DrawRectLines((Rectangle){rect.x - camera->rect.x, rect.y - camera->rect.y, rect.w, rect.h}, colour);
}

void DrawLine(Line line, SDL_Colour colour) {
	GPU_Line(globalTarget, line.startPoint.x, line.endPoint.y, line.endPoint.x, line.endPoint.y, colour);
}

void DrawTriangle(Tri* tri, SDL_Colour colour) {
	DrawLine((Line){tri->firstVert, tri->secondVert}, colour);
	DrawLine((Line){tri->secondVert, tri->thirdVert}, colour);
	DrawLine((Line){tri->thirdVert, tri->firstVert}, colour);
}

void DrawPoint(Vec2 point, SDL_Colour colour) {
	GPU_Pixel(globalTarget, point.x, point.y, colour);
}

void DrawPointMod(Vec2 point, SDL_Colour colour, Camera* camera) {
	if (PointInCamera(camera, point))
	DrawPoint((Vec2){point.x - camera->rect.x, point.y - camera->rect.y}, colour);
}

void DrawTexture(Bitmap* image, Rectangle* srcRect, Rectangle* dstRect) {
	DrawTextureEx(image, srcRect, dstRect, 0, &(Vec2){image->w / 2, image->h / 2}, 0);
}

void DrawTextureEx(Bitmap* image, Rectangle* srcRect, Rectangle* dstRect, double rotAngle, Vec2* centre, SDL_RendererFlip flip) {
	GPU_BlitRectX(image, srcRect, globalTarget, dstRect, rotAngle, centre->x, centre->y, flip);
}

void RenderBuffer() {
	GPU_Flip(globalTarget);
}

void SetRenderTarget(Bitmap* renderTarget) {
	if (renderTarget != NULL) {
		globalTarget = renderTarget->target;
	} else
		globalTarget = globalWindow->renderer;
}

void SetBlendMode(GPU_BlendPresetEnum blendMode) {
	GPU_SetShapeBlendMode(blendMode);
}