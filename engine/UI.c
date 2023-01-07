#include "UI.h"
#include "Array.h"
#include "Physics.h"

// Button

void InitButton(Button* button, char* text, Font* font) {
	button->text = text;
	button->font = *font;
	button->rect = (Rectangle){0, 0, 200, 50};
}

// Menu

void InitMenu(Menu* menu, char* menuText, int numButtons, Font* font) {
	menu->text = menuText;
	menu->numButtons = numButtons;

	menu->buttons = malloc(sizeof(Button) * numButtons);
	for (int i = 0; i < menu->numButtons; i++)
		menu->buttons[i] = NULL;
	
	printf("%p", menu->buttons[0]);
	menu->rect = (Rectangle){0, 0, 300, 500};
	menu->font = *font;

	CenterHoriz(&menu->rect, &(Rectangle){0, 0, globalWindow->width, globalWindow->height});
	CenterVert(&menu->rect, &(Rectangle){0, 0, globalWindow->width, globalWindow->height});

	LoadFontTextureWrap(&menu->font, menuText, menu->rect.w - 2, (SDL_Colour){0});	
}

void AddButtonToMenu(Menu* menu, Button* button) {
	// TODO: Fix!
	if (menu->buttons[menu->numButtons - 1] == NULL) {
		menu->buttons[FindPointerArray((void**)menu->buttons, NULL, menu->numButtons)] = button;
		CenterHoriz(&button->rect, &menu->rect);
		CenterVert(&button->rect, &menu->rect);
		LoadFontTextureWrap(&button->font, button->text, button->rect.w, (SDL_Colour){0});
		button->rect.y += 80;
	}
}

void RenderMenu(Menu* menu) {
	DrawRectR(menu->rect, 10, (SDL_Colour){128, 0, 128, 128});
	CenterHoriz(&menu->font.dRec, &menu->rect);
	CenterVert(&menu->font.dRec, &menu->rect);
	menu->font.dRec.y -= menu->rect.h / 4;
	DrawTexture(&menu->font.fontTex, NULL, &menu->font.dRec);
	for (int i = 0; i < menu->numButtons; i++) {
		if (menu->buttons[i] != NULL) {
			CenterHoriz(&menu->buttons[i]->font.dRec, &menu->buttons[i]->rect);
			CenterVert(&menu->buttons[i]->font.dRec, &menu->buttons[i]->rect);
			DrawRectR(menu->buttons[i]->rect, menu->buttons[i]->rect.h / 2, (SDL_Colour){0x30, 0x19, 0x34, 128});
			DrawTexture(&menu->buttons[i]->font.fontTex, NULL, &menu->buttons[i]->font.dRec);
		}
	}
}

void DestroyMenu(Menu* menu) {
	free(menu->buttons);
	CloseFont(&menu->font);
}