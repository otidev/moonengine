#include "Timer.h"

void SetTimer(Timer* timer, float limit) {
	timer->count = 0;
	timer->limit = limit;
	timer->isFinished = false;
}

void IncTimer(Timer* timer) {
	timer->count += GetDelta();
	if (timer->count >= timer->limit && timer->limit != 0 && !timer->isFinished)
		timer->isFinished = true;
}