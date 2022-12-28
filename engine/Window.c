#include "Window.h"
#include "Texture.h"
#include "Sound.h"
#include "Time.h"
#include "Array.h"
#include "Input.h"

Window* globalWindow;
GPU_Target* globalTarget;

int InitWindowEx(Window* window, int width, int height, char* windowName, uint32_t flags) {
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
		fprintf(stderr, "Man... SDL_INIT didn't work :( ");
		return EXIT_FAILURE;
	}
	// Window stuff
	window->width = width;
	window->height = height;
	window->window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->width, window->height, flags | SDL_WINDOW_OPENGL);

	GPU_SetInitWindow(SDL_GetWindowID(window->window));
	window->renderer = GPU_Init(width, height, flags);
	if (!window->renderer) {
		fprintf(stderr, "\033[1mError\033[0m: Couldn't initialize SDL and/or SDL_GPU: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	window->input = malloc(sizeof(Input));

	SetupInput(window->input);

	// Make arrays
	MakeArray(window->textureArray, TEXARRAYSIZE);
	MakeArray(window->musicArray, MUSICARRAYSIZE);
	MakeArray(window->soundArray, SOUNDARRAYSIZE);

	int imageSelection = IMG_INIT_PNG;
	if ((!IMG_Init(imageSelection)) & imageSelection) {
		fprintf(stderr, "\033[1mError\033[0m: Couldn't initialize SDL_IMG: %s\n", SDL_GetError());
	}

	if (TTF_Init() < 0) {
		fprintf(stderr, "\033[1mError\033[0m: Couldn't initialize SDL_TTF: %s\n", IMG_GetError()); // NIMP: ew compatibility
		return EXIT_FAILURE;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "\033[1mError\033[0m: Couldn't initialize SDL_TTF: %s\n", Mix_GetError());
		return EXIT_FAILURE;
	}

	window->gameRuns = true;
	
	globalWindow = window;
	globalTarget = window->renderer;
	return EXIT_SUCCESS;
}

int InitWindow(Window* window, int width, int height, char* windowName) {
	return InitWindowEx(window, width, height, windowName, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

void End() {
	// Close input
	CloseInput(globalWindow->input);
	Mix_CloseAudio();

	FreeTexArray((Bitmap**)globalWindow->textureArray, TEXARRAYSIZE);
	FreeMusicArray((Music**)globalWindow->musicArray, MUSICARRAYSIZE);
	FreeSoundArray((Sound**)globalWindow->soundArray, SOUNDARRAYSIZE);

	SDL_DestroyWindow(globalWindow->window); // what

	// Quit SDL and derivs
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	GPU_Quit();
	SDL_Quit();
}

static void HandleEvents() {
	while (SDL_PollEvent(&globalWindow->event)) {
		switch (globalWindow->event.type) {
			case SDL_QUIT:
				globalWindow->gameRuns = false;
				break;
			// Joystick motion
			case SDL_JOYAXISMOTION:
				if (globalWindow->event.jaxis.which == 0) {
					// X axis
					if (globalWindow->event.jaxis.axis == 0) {

						if (globalWindow->event.jaxis.value < -globalWindow->input->joystickDeadzone)
							globalWindow->input->inputH = -1;
						else if (globalWindow->event.jaxis.value > globalWindow->input->joystickDeadzone)
							globalWindow->input->inputH = 1;
						else
							globalWindow->input->inputH = 0;
					}

					// Y axis
					if (globalWindow->event.jaxis.axis == 1) {
						if (globalWindow->event.jaxis.value < -globalWindow->input->joystickDeadzone)
							globalWindow->input->inputV = -1;
						else if (globalWindow->event.jaxis.value > globalWindow->input->joystickDeadzone)
							globalWindow->input->inputV = 1;
						else
							globalWindow->input->inputV = 0;
					}
				}
				break;
			// Keypresses
			case SDL_KEYDOWN:
				if (globalWindow->event.key.repeat == 0)
					globalWindow->input->keyState[globalWindow->event.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				if (globalWindow->event.key.repeat == 0)
					globalWindow->input->keyState[globalWindow->event.key.keysym.scancode] = false;
				break;
			case SDL_JOYBUTTONDOWN:
				globalWindow->input->controllerButton[globalWindow->event.jbutton.button] = true;
				break;
			case SDL_JOYBUTTONUP:
				globalWindow->input->controllerButton[globalWindow->event.jbutton.button] = false;
				break;
			case SDL_MOUSEMOTION:
				int x, y;
				SDL_GetMouseState(&x, &y);
				globalWindow->input->mousePos.x = x;
				globalWindow->input->mousePos.y = y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				globalWindow->input->mouseButton[globalWindow->event.button.button - 1] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				globalWindow->input->mouseButton[globalWindow->event.button.button - 1] = false;
				break;
		}
	}
}

bool WindowIsOpen(int fps) {
	EndCounter();
	InitCounter();

	for (int i = 0; i < 256; i++) {
		globalWindow->input->keyStatePrev[i] = globalWindow->input->keyState[i];
	}
	HandleEvents();

	if (!(fps < 1))
		SetFPS(fps);
	return globalWindow->gameRuns;
}