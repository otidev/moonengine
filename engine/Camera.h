#ifndef MOON_ENGINE_CAMERA_H
#define MOON_ENGINE_CAMERA_H

#include "Include.h"

// Initialises a camera struct
void InitCamera(Camera* camera, int width, int height);

// Adjusts camera if out of its bounds
void CheckCameraBounds(Camera* camera);

// Sets bounds, then checks camera bounds
void CheckCameraBoundsExt(Camera* camera, Rectangle* rec);

// Sets a camera scale
void SetCameraScale(Camera* camera);

// Returns the camera offset
Vec2 CameraOffset(Camera* camera);

// Returns true if the rectangle is in the view of the camera
bool RectangleInCamera(Camera* camera, Rectangle rec);

// Returns true if the point is in the view of the camera
bool PointInCamera(Camera* camera, Vec2 vec);

#endif