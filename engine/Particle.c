#include "Particle.h"
#include "Physics.h"
#include "Sprite.h"

void InitParticle(Particle* particle, int width, int height, Vec2 pos, Vec2 speed, int frameDeath) {
	InitSpriteNoTex(&particle->spr, width, height);
	RectToVec2(pos, &particle->spr.dRec);
	particle->speed = speed;
	particle->isAlive = true;
	particle->lifetime = 0;
	particle->frameDeath = frameDeath;
}

void UpdateParticle(Particle* particle) {
	// I know there's a function for this, but I don't want to add a Vector for positions.
	particle->spr.dRec.x += particle->speed.x * GetDelta();
	particle->spr.dRec.y += particle->speed.y * GetDelta();
	if (particle->lifetime >= particle->frameDeath)
		DestroyParticle(particle);
	else
		particle->lifetime++;
}

void DestroyParticle(Particle* particle) {
	particle->isAlive = false;
	particle->spr.visible = false;
}