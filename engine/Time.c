#include "Time.h"

// Starts counting for deltatime.
static u64 timeStart;
// Stops counting for deltatime.
static u64 timeEnd;
// Deltatime.
static float timeElapsed;

void InitCounter(void) {
	// Start timer.
	timeStart = SDL_GetTicks();
}

void EndCounter(void) {
	// End timer.
	timeEnd = SDL_GetTicks();

	// NOTE: Multiply by 0.001 because SDL_GetTicks returns in the thousands.
	timeElapsed = (timeEnd - timeStart) * 0.001;
	#ifdef DEBUG
		// Prints FPS.
		if ((timeEnd - timeStart) > 0) fprintf(stderr, "FPS: %f\n", GetFPS());
		// Prints deltatime
		fprintf(stderr, "Delta: %f ", timeElapsed);
	#endif
}

float GetDelta(void) {
	return timeElapsed;
}

void SetFPS(float fps) {
	if (1000/fps > SDL_GetTicks() - timeStart) {
		SDL_Delay(1000/fps - (SDL_GetTicks() - timeStart));
	}
}

double GetFPS(void) {
	return 1000 / (double) (timeEnd - timeStart);
}