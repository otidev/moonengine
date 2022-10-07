#ifndef MOON_ENGINE_THREEDIM_H
#define MOON_ENGINE_THREEDIM_H

#include "Include.h"
#include "Physics.h"
#include "Rendering.h"


typedef struct Mesh {
	Vec3* triangles;
	int indexCount;
} Mesh;

typedef struct Mat4x4 {
	float matrix[4][4];
} Mat4x4;

// Creates a 3D projection matrix
void CreateProjMatrix(float fov, float zNear, float zFar, float aspectRat, Mat4x4* srcMatrix);

// Multiplies a 4x4 matrix with a vector, writes into Vec3* out
void MatrixMult(Vec3 in, Vec3* out, Mat4x4* matrix);

void something(SDL_Renderer* renderer);

#endif