#ifndef MOON_ENGINE_TIME_H
#define MOON_ENGINE_TIME_H

#include "Include.h"

// Starts counting for delatime.
void InitCounter(void);

// Stops counting for deltatime, then calculates it.
void EndCounter(void);

// Returns deltatime.
float GetDelta(void);

// Sets FPS.
void SetFPS(float fps);

// Gets FPS.
float GetFPS(void);

#endif