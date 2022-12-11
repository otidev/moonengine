#include "3D.h"

void CreateProjMatrix(float fov, float zNear, float zFar, float aspectRat, Mat4x4* srcMatrix) {
	float scale = 1 / tanf(fov / 2 * M_PI / 180);
	float matrix[4][4] = {
		{scale * aspectRat, 0, 0, 0},
		{0, scale, 0, 0},
		{0, 0, -(zFar / (zFar - zNear)), -1},
		{0, 0, -((zFar * zNear) / (zFar - zNear)), 0}
	};

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++)
			srcMatrix->matrix[i][j] = matrix[i][j];
	}
}

void MatrixMult(Vec3 in, Vec3* out, Mat4x4* matrix) {
	out->x = in.x * matrix->matrix[0][0] + in.y * matrix->matrix[1][0] + in.z * matrix->matrix[2][0] + matrix->matrix[3][0];
	out->y = in.x * matrix->matrix[0][1] + in.y * matrix->matrix[1][1] + in.z * matrix->matrix[2][1] + matrix->matrix[3][1];
	out->z = in.x * matrix->matrix[0][2] + in.y * matrix->matrix[1][2] + in.z * matrix->matrix[2][2] + matrix->matrix[3][2];
	float w = in.x * matrix->matrix[0][3] + in.y * matrix->matrix[1][3] + in.z * matrix->matrix[2][3] + matrix->matrix[3][3];

	if (w != 0) {
		out->x /= w;
		out->y /= w;
		out->z /= w;
	}
}

void something(SDL_Renderer* renderer) {
	Mat4x4 matrix;

	Vec3 cubetverts[36] = {
		// SOUTH
		{0.0f, 0.0f, 0.0f},	{0.0f, 1.0f, 0.0f},	{1.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 0.0f},	{1.0f, 0.0f, 0.0f},

		// EAST	
		{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 0.0f},	{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f},	{1.0f, 0.0f, 1.0f},

		// NORTH	 
		{1.0f, 0.0f, 1.0f},	{1.0f, 1.0f, 1.0f},	{0.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},	{0.0f, 1.0f, 1.0f},	{0.0f, 0.0f, 1.0f},

		// WEST	
		{0.0f, 0.0f, 1.0f},	{0.0f, 1.0f, 1.0f},	{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},	{0.0f, 1.0f, 0.0f},	{0.0f, 0.0f, 0.0f},

		// TOP	 
		{0.0f, 1.0f, 0.0f},	{0.0f, 1.0f, 1.0f},	{1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},	{1.0f, 1.0f, 1.0f},	{1.0f, 1.0f, 0.0f},

		// BOTTOM	
		{1.0f, 0.0f, 1.0f},	{0.0f, 0.0f, 1.0f},	{0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 1.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 0.0f, 0.0f},

	};

	Mesh meshCube = {cubetverts, 12};

	float zNear = 0.1f;
	float zFar = 1000.0f;
	float fov = 90.0f;

	CreateProjMatrix(fov, zNear, zFar, (320/240), &matrix);

	for (int i = 0; i < meshCube.indexCount; i += 3) {

		meshCube.triangles[i].z += 3;
		meshCube.triangles[i + 1].z += 3;
		meshCube.triangles[i + 2].z += 3;

		Vec3 tris[3] = {
			meshCube.triangles[i],
			meshCube.triangles[i + 1],
			meshCube.triangles[i + 2]
		};

		MatrixMult(meshCube.triangles[i], &tris[0], &matrix);
		MatrixMult(meshCube.triangles[i + 1], &tris[1], &matrix);
		MatrixMult(meshCube.triangles[i + 2], &tris[2], &matrix);
		tris[0].x += 1; tris[0].y += 1;
		tris[1].x += 1; tris[1].y += 1;
		tris[2].x += 1; tris[2].y += 1;
		tris[0].x *= 320 / 2; tris[0].y *= 240 / 2;
		tris[1].x *= 320 / 2; tris[1].y *= 240 / 2;
		tris[2].x *= 320 / 2; tris[2].y *= 240 / 2;

		Tri triangle;
		triangle.firstVert = (Vec2){tris[0].x, tris[0].y};
		triangle.secondVert = (Vec2){tris[1].x, tris[1].y};
		triangle.thirdVert = (Vec2){tris[2].x, tris[2].y};
		DrawTriangle(&triangle, (SDL_Colour){0, 0, 0, 0});
	}
}