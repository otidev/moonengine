#ifndef MOON_ENGINE_INPUT_H
#define MOON_ENGINE_INPUT_H

#include "Include.h"

// Sets up input (allocation not done).
void SetupInput(Input* input);

// Frees an input pointer
void CloseInput(Input* input);

// Checks if a key is pressed.
bool KeyPressed(unsigned char scancode, Input* input);

// Checks if a key has just been pressed.
bool KeyJustPressed(unsigned char scancode, Input* input);

// Checks if a gamepad button is pressed.
bool GameButtonPressed(int button, Input* input);

// Checks if a mouse button is pressed.
bool MouseButtonPressed(unsigned char button, Input* input);

#endif