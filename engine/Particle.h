#ifndef MOON_ENGINE_PARTICLE_H
#define MOON_ENGINE_PARTICLE_H

#include "Include.h"

// Initialise a particle
void InitParticle(Particle* particle, int width, int height, Vec2 pos, Vec2 speed, int frameDeath);

// Updates a particle
void UpdateParticle(Particle* particle);

// Destroys a particle
void DestroyParticle(Particle* particle);

#endif