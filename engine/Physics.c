#include "Physics.h"

float Lerp(float a, float b, float t) {
	return a + t * (b - a);
}

float Smoothstep(float a, float b, float t) {
	float scaled = (3 * (t * t)) - (2 * (t * t * t));
	return Lerp(a, b, scaled);
}

float Sign(float x) {
	return (x > 0) - (x < 0);
}

bool RectangleCollide(Rectangle a, Rectangle b) {
	// Checks if the AABB formula is true.
	if (a.x <= b.x + b.w &&
		a.x + a.w >= b.x &&
		a.y <= b.y + b.h &&
		a.y + a.h >= b.y) 
		return true;
	else
		return false;
}

bool RectanglePointCollide(Rectangle rect, Vec2 vec) {
	if (vec.x >= rect.x &&
		vec.x <= rect.x + rect.w &&
		vec.y >= rect.y &&
		vec.y <= rect.y + rect.h)
		return true;
	else
		return false;
}

bool RectangleSideCollide(Rectangle a, Rectangle b, RectSide side) {
	Vec2 leftTop = (Vec2){b.x, b.y + 1};
	Vec2 leftMid = (Vec2){b.x, b.y + (b.h / 2)};
	Vec2 leftBot = (Vec2){b.x, b.y + b.h - 1};
	
	Vec2 rightTop = (Vec2){b.x + b.w, b.y + 1};
	Vec2 rightMid = (Vec2){b.x + b.w, b.y + (b.h / 2)};
	Vec2 rightBot = (Vec2){b.x + b.w, b.y + b.h - 1};
	
	Vec2 topMid = (Vec2){b.x + (b.w / 2), b.y};
	Vec2 bottomMid = (Vec2){b.x + (b.w / 2), b.y + b.h};

	if (side == LEFT && (RectanglePointCollide(a, leftTop) || RectanglePointCollide(a, leftMid) || RectanglePointCollide(a, leftBot)))
			return true;
	if (side == RIGHT && (RectanglePointCollide(a, rightTop) || RectanglePointCollide(a, rightMid) || RectanglePointCollide(a, rightBot)))
			return true;
	if (side == TOP && RectanglePointCollide(a, topMid))
			return true;
	if (side == BOTTOM && RectanglePointCollide(a, bottomMid))
			return true;
	
	return false;
}

void RecordVels(Vec2 vec, Vec2 *pos) {
	pos->x += vec.x * GetDelta();
	pos->y += vec.y * GetDelta();
}

void RectToVec2(Vec2 vec, Rectangle *rect) {
	rect->x = (int)vec.x;
	rect->y = (int)vec.y;
}

void Vec2ToRect(Rectangle rect, Vec2 *vec) {
	vec->x = (float)rect.x;
	vec->y = (float)rect.y;
}

bool Vec2IsTo(Vec2* a, Vec2* b) {
	if (a->x == b->x && a->y == b->y)
		return true;
	else
		return false;
}

float GetLineDir(Line line) {
	// im not good at making formulas, im just good at writing code.
	float value = (atan2((line.endPoint.y - line.startPoint.y), (line.endPoint.x - line.startPoint.x)) * 180) / M_PI;
	return (value > 0) ? value : (360 + value);
}

bool RectangleInBounds(Rectangle* a, Rectangle* b) {
	if (!(a->x < b->x) && !(a->y < b->y) && !((a->x + a->w) > (b->x + b->w)) && !((a->y + a->h) > (b->y + b->h)))
		return true;
	else
		return false;
}

bool RectIsTo(Rectangle* a, Rectangle* b) {
	if (a->x == b->x && a->y == b->y && a->w == b->w && a->y == b->y)
		return true;
	else
		return false;
}

void AssignVec2(Vec2 a, Vec2 b) {
	a.x = b.x;
	a.y = b.y;
}

void CenterHoriz(Rectangle* a, Rectangle* b) {
	// We do calculations on these
	Rectangle calA = (Rectangle){0};
	Rectangle calB = (Rectangle){0};
	float offset;
	
	calA.w = a->w;
	calB.w = b->w;

	if (!(calB.w == calA.w)) {
		offset = calB.w - calA.w;
		a->x = b->x;
		a->x += offset / 2;
		a->x += calB.x;
	} else {
		b->x = a->x;
	}
}

void CenterVert(Rectangle* a, Rectangle* b) {
	// Same as other one
	Rectangle calA = (Rectangle){0};
	Rectangle calB = (Rectangle){0};
	float offset;
	
	calA.h = a->h;
	calB.h = b->h;

	if (!(calB.h == calA.h)) {
		offset = calB.h - calA.h;
		a->y = b->y;
		a->y += offset / 2;
		a->y += calB.y;
	} else {
		b->y = a->y;
	}
}