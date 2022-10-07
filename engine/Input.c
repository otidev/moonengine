#include "Input.h"

void SetupInput(Input* input) {

	// Set all keystates to 0.
	for (int i = 0; i < 256; i++) {
   		input->keyState[i] = false;
		input->keyStatePrev[i] = false;
		if (i < 5)
			input->mouseButton[i] = false;
	}
	
	if (SDL_NumJoysticks() < 1) {
		fprintf(stderr, "No joysticks connected!\n");
	}

	input->controller = SDL_JoystickOpen(0);

	input->joystickDeadzone = 3200;
}

void CloseInput(Input* input) {
	free(input);
}

bool KeyPressed(unsigned char scancode, Input* input) {
	return input->keyState[scancode];
}

bool KeyJustPressed(unsigned char scancode, Input* input) {
	return input->keyState[scancode] > input->keyStatePrev[scancode];
}

bool GameButtonPressed(int button, Input* input) {
	return input->controllerButton[button];
}

bool MouseButtonPressed(unsigned char button, Input* input) {
	return input->mouseButton[button];
}