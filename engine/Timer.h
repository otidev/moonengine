#ifndef MOON_ENGINE_TIMER_H
#define MOON_ENGINE_TIMER_H

#include "Include.h"
#include "Time.h"

// Initialises a timer
void SetTimer(Timer* timer, float limit);

// Increments and signifies if a timer is up or not.
void IncTimer(Timer* timer);

#endif