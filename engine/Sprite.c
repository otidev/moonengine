#include "Sprite.h"
#include "Physics.h"
#include "Camera.h"

float timer = 0;
// Only used here to do frame calulations.
int frame = 0;

void PlayAnim(Sprite *spr, float updateTime) {
	// Geting full width of texture
	int sizew = spr->tex.w;
	// Adds deltatime to the timer.
	timer += GetDelta();

	if (timer >= updateTime) {
		// Add the width of a frame to the x value.
		spr->sRec.x += (sizew / spr->frames);
		// Reset the timer to 0.
		timer = 0;
		if (spr->sRec.x == sizew) {
			// Reset x to 0.
			spr->sRec.x = 0;
		}
	}

}

void RenderSprite(Sprite* spr) {
	SDL_RendererFlip flip;
	if (spr->visible) {
		if (!spr->facingRight)
			flip = SDL_FLIP_HORIZONTAL;
		else
			flip = SDL_FLIP_NONE;

		GPU_SetColor(&spr->tex, spr->colour);
		DrawTextureEx(&spr->tex, &spr->sRec, &spr->dRec, spr->rotation, &spr->center, flip);
	}
}

void  RenderSpriteMod(Sprite* spr, Camera* camera) {
	// TODO: Fix this, because it's broken :<(=-=:
	if (RectangleInCamera(camera, spr->dRec)) {
		spr->dRec.x -= camera->rect.x;
		spr->dRec.y -= camera->rect.y;
		printf("%p\n", spr->tex.data);
		RenderSprite(spr);
		spr->dRec.x += camera->rect.x;
		spr->dRec.y += camera->rect.y;
	}
}

static void InitSpriteData(Sprite *spr) {
	spr->scale = (Vec2){1, 1};
	spr->visible = true;
	spr->colour = (SDL_Colour){0xff, 0xff, 0xff, 0xff};
	spr->center = SPR_MIDDLE(spr);

	// Set source rect and destination rect.
	spr->sRec = (Rectangle){0, 0, spr->width, spr->height};
	spr->dRec = (Rectangle){0, 0, spr->width / spr->scale.x, spr->height / spr->scale.y};

	spr->facingRight = true;
}

void InitSprite(Sprite *spr, int width, int height, char* textureFilename) {
	spr->width = width;
	spr->height = height;
	InitSpriteData(spr);
	spr->tex = LoadTexture(textureFilename);
}

void InitSpriteNoTex(Sprite *spr, int width, int height) {
	spr->width = width;
	spr->height = height;
	InitSpriteData(spr);

	SDL_Surface* surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	uint32_t* pixels;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pixels = (uint32_t*)(surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel);
			*pixels = 0xffffffff;
		}
	}
	spr->tex = CreateTextureFromSurface(surf);

}

void SetScale(Sprite* spr) {
	spr->dRec = (Rectangle){spr->dRec.x, spr->dRec.y, spr->width * spr->scale.x, spr->height * spr->scale.y};
}