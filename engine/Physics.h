#ifndef MOON_ENGINE_PHYSICS_H
#define MOON_ENGINE_PHYSICS_H

#include "Include.h"
#include "Time.h"

// Linear interpolation function
float Lerp(float a, float b, float t);

// Smooth steping function
float Smoothstep(float a, float b, float t);

// Returns sign of a number (-1 or 1)
float Sign(float x);

// Does AABB between two rects, returns true if there is collision.
bool RectangleCollide(Rectangle a, Rectangle b);

// Rectangle point collision.
bool RectanglePointCollide(Rectangle rect, Vec2 vec);

// Does AABB between two rects, returns true if there is collision on a particular side.
bool RectangleSideCollide(Rectangle a, Rectangle b, RectSide side);

// Calculates transforms a vector.
void Transform(Vec2 *srcVec, Vec2 transVec);

// Stores the data from the first param to the second.
void RecordVels(Vec2 vec, Vec2 *pos);

// Takes data from a rect and puts it in a Vec2.
void RectToVec2(Vec2 vec, Rectangle *rect);

// Takes data from a Vec2 and puts it in a rect.
void Vec2ToRect(Rectangle rect, Vec2 *vec);

// Get the direction a line is pointing.
float GetLineDir(Line line);

// Returns true if both vectors are equal.
bool Vec2IsTo(Vec2* a, Vec2* b);

// Returns true if rectangle A is in B's bounds.
bool RectangleInBounds(Rectangle* a, Rectangle* b);

// Returns true if both rectangles are equal (same proportions).
bool RectIsTo(Rectangle* a, Rectangle* b);

// Assigns first vector to the second.
void AssignVec2(Vec2 a, Vec2 b);

// Centers two rectangles horizontally.
void CenterHoriz(Rectangle* a, Rectangle* b);

// Centers two rectangles vertically.
void CenterVert(Rectangle* a, Rectangle* b);

#endif