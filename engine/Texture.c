#include "Texture.h"
#include "Array.h"

int baseArraySize;

Bitmap LoadTexture(char* filename) {
	// Load the image into a surface
	Bitmap* tex = GPU_LoadImage(filename);


	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	GPU_SetImageFilter(tex, GPU_FILTER_NEAREST);
	return *tex;
}

Bitmap CreateTexture(int width, int height) {
	Bitmap* tex = GPU_CreateImage(width, height, GPU_FORMAT_RGBA);
	GPU_SetImageFilter(tex, GPU_FILTER_NEAREST);

	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	return *tex;
}

Bitmap CreateRenderTarget(int width, int height) {
	Bitmap* tex = GPU_CreateImage(width, height, GPU_FORMAT_RGBA);
	GPU_SetImageFilter(tex, GPU_FILTER_NEAREST);
	GPU_LoadTarget(tex);
	
	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	return *tex;
}

void DestroyRenderTarget(Bitmap* bitmap) {
	GPU_FreeTarget(bitmap->target);
}

Bitmap CreateTextureFromSurface(SDL_Surface* surf) {
	Bitmap* tex = GPU_CopyImageFromSurface(surf);
	GPU_SetImageFilter(tex, GPU_FILTER_NEAREST);

	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	return *tex;
}

void FreeTexArray(Bitmap *arrayPtr[], int size) {
	if (size == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	int i = 0;

	for (i = 0; i < size; i++) {
		if (arrayPtr[i] != NULL) {
			GPU_FreeImage(arrayPtr[i]);

			#ifdef DEBUG
				fprintf(stderr, "Unloaded pointer to texture: %p\n", arrayPtr[i]);
			#endif
		}
	}
}