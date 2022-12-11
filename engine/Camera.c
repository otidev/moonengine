#include "Camera.h"
#include "Physics.h"

void InitCamera(Camera* camera, int width, int height) {
	camera->rect.w = camera->orig.w = width;
	camera->rect.h = camera->orig.h = height;
	camera->scale = (Vec2){1, 1};
	camera->bounds = (Rectangle){0, 0, camera->rect.w, camera->rect.h};
}

void CheckCameraBounds(Camera* camera) {
	// Making right and bottom camera bounds because it can get long w/o variables
	int rightBoundCam = camera->rect.x + camera->rect.w;
	int rightBound = camera->bounds.x + camera->bounds.w;
	int bottomBoundCam = camera->rect.y + camera->rect.h;
	int bottomBound = camera->bounds.y + camera->bounds.h;

	// Checks
	if (camera->rect.x < camera->bounds.x)
		camera->rect.x = camera->bounds.x;
	if (camera->rect.y < camera->bounds.y)
		camera->rect.y = camera->bounds.y;
	if (rightBoundCam > rightBound)
		camera->rect.x = rightBound - camera->rect.w;
	if (bottomBoundCam > bottomBound)
		camera->rect.y = bottomBound - camera->rect.h;
}

void CheckCameraBoundsExt(Camera* camera, Rectangle* rec) {
	camera->bounds = *rec;
	CheckCameraBounds(camera);
}

void SetCameraScale(Camera* camera) {
	camera->rect.w = camera->scale.x > 1 ? camera->orig.w / camera->scale.x : camera->orig.w * camera->scale.x;
	camera->rect.h = camera->scale.y > 1 ? camera->orig.h / camera->scale.y : camera->orig.h * camera->scale.y;
}

Vec2 CameraOffset(Camera* camera) {
	return (Vec2){camera->rect.x, camera->rect.y};
}

bool RectangleInCamera(Camera* camera, Rectangle rec) {
	if (RectangleCollide(camera->rect, rec) || !camera)
		return true;
	else
		return false;
}

bool PointInCamera(Camera* camera, Vec2 vec) {
	if (RectanglePointCollide(camera->rect, vec))
		return true;
	else
		return false;
}