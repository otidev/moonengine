#include "Texture.h"
#include "Array.h"

int baseArraySize;

Bitmap LoadTexture(char* filename) {
	// Load the image into a surface
	SDL_Surface *surf = IMG_Load(filename);
	
	if (surf == NULL) {
		fprintf(stderr, "\033[1mError\033[0m: Loading a surface from file didn't work: %s ", IMG_GetError());
		return NULL;
	}
	// Take the surface data into texture data
	Bitmap tex = SDL_CreateTextureFromSurface(globalWindow->renderer, surf);
	
	if (tex == NULL) {
		fprintf(stderr, "\033[1mError\033[0m: Loading a texture didn't work: %s ", SDL_GetError());
		return NULL;
	}

	// Delete the surface
	SDL_FreeSurface(surf);
	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	return tex;
}

Bitmap CreateTexture(uint32_t byteFormat, int textureAccess, int width, int height) {
	Bitmap tex = SDL_CreateTexture(globalWindow->renderer, byteFormat, textureAccess, width, height);
	// This is the reason this exists
	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	return tex;
}

Bitmap CreateTextureFromSurface(SDL_Surface* surf) {
	Bitmap tex = SDL_CreateTextureFromSurface(globalWindow->renderer, surf);
	// This is the reason this exists (again)
	AddToArray(globalWindow->textureArray, tex, TEXARRAYSIZE);
	return tex;
}

void FreeTexArray(Bitmap *arrayPtr[], int size) {
	if (size == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	int i = 0;

	while (arrayPtr[i] != NULL) {
		#ifdef DEBUG
			fprintf(stderr, "Unloaded pointer to texture: %p\n", arrayPtr[i]);
		#endif

		SDL_DestroyTexture(*arrayPtr[i]);
		i++;
	}
}