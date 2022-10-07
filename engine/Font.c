#include "Font.h"

void InitFont(Font* font, char* filename, int fontSize) {
	font->font = TTF_OpenFont(filename, fontSize);
}

void LoadFontTexture(Font* font, char* text, SDL_Colour colour) {
	SDL_Surface* surf = TTF_RenderUTF8_Solid(font->font, text, colour);
	font->sRec.w = font->dRec.w = surf->w;
	font->sRec.h = font->dRec.h = surf->h;
	font->fontTex = CreateTextureFromSurface(surf);
	SDL_FreeSurface(surf);
}

void LoadFontTextureWrap(Font* font, char* text, int wrapWidth, SDL_Colour colour) {
	SDL_Surface* surf = TTF_RenderUTF8_Solid_Wrapped(font->font, text, colour, wrapWidth);
	font->sRec.w = font->dRec.w = surf->w;
	font->sRec.h = font->dRec.h = surf->h;
	font->fontTex = CreateTextureFromSurface(surf);
	SDL_FreeSurface(surf);
}

void CloseFont(Font* font) {
	TTF_CloseFont(font->font);
}