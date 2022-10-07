#ifndef MOON_ENGINE_TYPES_H
#define MOON_ENGINE_TYPES_H

// Texture array size
#define TEXARRAYSIZE 1024
// Sound array size
#define SOUNDARRAYSIZE 2048
// Music array size
#define MUSICARRAYSIZE 256

#include <SDL.h>

typedef SDL_Rect Rectangle;
// NOTE: This is a pointer!!
typedef SDL_Texture* Bitmap;

// A 2D vector struct.
typedef struct Vec2 {
	float x;
	float y;
} Vec2;

// A 3D vector struct.
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

// A line struct
typedef struct Line {
	Vec2 startPoint;
	Vec2 endPoint;
} Line;

// A 3D line struct
typedef struct Line3 {
	Vec3 startPoint;
	Vec3 endPoint;
} Line3;

// A 2D triangle struct.
typedef struct Tri {
	Vec2 firstVert;
	Vec2 secondVert;
	Vec2 thirdVert;
} Tri;

// A 3D triangle struct.
typedef struct Tri3 {
	Vec3 firstVert;
	Vec3 secondVert;
	Vec3 thirdVert;
} Tri3;

// A hitbox struct.
typedef struct Hitbox {
	Vec2 pos;
	// Collidable flag
	bool collidable;
	Rectangle box;
} Hitbox;

// A struct the same as Hitbox, but a different name to avoid confusion. 
typedef struct Hitbox Hurtbox;

// A sprite struct type for a sprite's texture and their surface, the both the source and destination rectangles. 
typedef struct Sprite {
	// Texture
	Bitmap tex;
	// Source rectangle
	Rectangle sRec;
	// Destination rectangle
	Rectangle dRec;
	// Sprite width and height
	int width;
	int height;
	// Animation frame.
	int frame;
	// Center of rotation.
	Vec2 center;
	// Facing right or left
	bool facingRight;
	// Scaling vector
	Vec2 scale;
	float rotation; // Rotation
	bool visible; // Visibility flag
	SDL_Colour colour; // Colour
} Sprite;

typedef enum GamepadButtons {
	// PAD_RIGHT_ is for the ABXY or the PS5 stuff
	PAD_RIGHT_BOTTOM,
	PAD_RIGHT_RIGHT,
	PAD_RIGHT_LEFT,
	PAD_RIGHT_TOP,
	PAD_LEFTBUMP,
	PAD_RIGHTBUMP,
	// SNES naming convention
	PAD_SELECT,
	PAD_START,
	PAD_LEFTSTICK,
	PAD_RIGHTSTICK,
	PAD_DPAD_UP,
	PAD_DPAD_DOWN,
	PAD_DPAD_LEFT,
	PAD_DPAD_RIGHT
} GamepadButtons;

typedef struct Input {
	// Keystates (SDL_SCANCODE)
	bool keyState[256];
	// Keystates for previous frame (SDL_SCANCODE)
	bool keyStatePrev[256];
	// Gamepad
	SDL_Joystick* controller;
	bool controllerButton[22];
	// Gamepad stick deadzone
	int joystickDeadzone;
	// Horizontal and vertical inputs
	float inputH;
	float inputV;

	// Mouse handling
	Vec2 mousePos;
	bool mouseButton[5];
} Input;

typedef struct Window {
	// Window event
	SDL_Event event;
	// Main window
	SDL_Window *window;
	// Main renderer
	SDL_Renderer *renderer;
	// Game-runnning loop bool
	bool gameRuns;

	// Texture array (of Bitmap *)
	void* textureArray[TEXARRAYSIZE];
	// Music array (of Mix_Music *)
	void* musicArray[MUSICARRAYSIZE];
	// Sound array (of Mix_Chunk *)
	void* soundArray[SOUNDARRAYSIZE];

	// Window input
	Input* input;

	// Window width
	int width;
	// Window height
	int height;
} Window;

// An entity struct type containing a hit/hurtbox, velocity, positioning, a sprite, etc.
typedef struct Entity {
	// Hitbox
	Hitbox hit;
	// Hurtbox
	Hurtbox hurt;
	// Speed vector
	Vec2 speed;
	// Position vector
	Vec2 pos;
	// Entity sprite
	Sprite spr;
} Entity;

typedef struct Font {
	// TTF font
	TTF_Font* font;
	// Font texture used for rendering
	Bitmap fontTex;

	// Source rect and dest rect
	Rectangle sRec;
	Rectangle dRec;
} Font;

typedef enum RectSide {
	NONE = 0,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
} RectSide;

typedef struct Music {
	Mix_Music* music;
	double lastPlayPos;
} Music;

typedef struct Sound {
	Mix_Chunk* sound;
} Sound;

typedef struct Camera {
	Rectangle rect;
	Rectangle orig;
	Rectangle bounds;
	Vec2 scale;
	bool specialCase;
} Camera;

typedef struct Particle {
	Sprite spr;
	Vec2 speed;
	bool isAlive;
	int lifetime;
	int frameDeath;
} Particle;

#endif