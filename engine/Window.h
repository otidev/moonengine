#ifndef MOON_ENGINE_WINDOW_H
#define MOON_ENGINE_WINDOW_H

#include "Include.h"

extern Window* globalWindow;

// Initialises a window (extended params).
int InitWindowEx(Window* window, int width, int height, char* windowName, uint32_t flags);

// Initialises a window.
int InitWindow(Window* window, int width, int height, char* windowName);

// Runs at the end of the program
void End();

// Runs while the window is open and sets fps (0 for no target)
bool WindowIsOpen(int fps);

#endif