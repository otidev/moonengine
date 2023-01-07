#ifndef MOON_ENGINE_UI_H
#define MOON_ENGINE_UI_H

#include "Include.h"
#include "Font.h"
#include "Rendering.h"

// Initialises a button
void InitButton(Button* button, char* text, Font* font);

// Initialises a menu
void InitMenu(Menu* menu, char* menuText, int numButtons, Font* font);

// Adds a button to a menu
void AddButtonToMenu(Menu* menu, Button* button);

// Renders a menu
void RenderMenu(Menu* menu);

// Destroys a menu struct
void DestroyMenu(Menu* menu);

#endif