#ifndef MOON_ENGINE_TYPES_H
#define MOON_ENGINE_TYPES_H

// Texture array size
#define TEXARRAYSIZE 4096
// Sound array size
#define SOUNDARRAYSIZE 2048
// Music array size
#define MUSICARRAYSIZE 256

#include <SDL.h>

typedef GPU_Rect Rectangle;
// NOTE: This is a pointer!!
typedef GPU_Image Bitmap;

#define COLOUR_FULL (SDL_Colour){0xff, 0xff, 0xff, 0xff}

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

typedef struct Timer {
	float count;
	// If the limit is 0, the timer will go on forever.
	float limit;
	// Turns true when the counter is finished.
	bool isFinished;
} Timer;

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
	// How many frames in animation.
	int frames;
	// Center of rotation.
	Vec2 center;
	// Facing right or left
	bool facingRight;
	// Scaling vector
	Vec2 scale;
	// Rotation
	float rotation;
	// Visibility flag
	bool visible;
	// Colour
	SDL_Colour colour;
	// The timer for the sprite animation (handle with care!)
	Timer timer;
} Sprite;

#define SPR_MIDDLE(spr) (Vec2){spr->width / 2, spr->height / 2};
#define SPR_MIDDLE_LIT(spr) (Vec2){spr.width / 2, spr.height / 2};

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
	GPU_Target* renderer;
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

extern Window* globalWindow;
extern GPU_Target* globalTarget;

typedef struct Tileset {
	// First/last GID number
	int firstgid;
	int lastgid;
	// Texture for rendering
	Bitmap texture;
	// Array of tile groups (in order of gid)
	char* tileGroup[1024];
} Tileset;

typedef struct Map {
	char filename[1024];
	// Width of map
	int width;
	// Height of map
	int height;
	// Texture used for rendering
	Bitmap mapRenderTexture;

	// Tilemap data (fg and bg)
	uint32_t mapFg[1000][1000];
	uint32_t mapBg[1000][1000];

	// Tile width and height
	int tileWidth;
	int tileHeight;

	// Tilesets
	Tileset tileset[128];
	int numTilesets;

	char mapColl[1000][1000];
	// Rectangle for map collisions
	Rectangle collisionRect;
} Map;


// An entity struct type containing a hit/hurtbox, velocity, positioning, a sprite, etc.
typedef struct Entity {
	// Hitbox
	Hitbox hit;
	// Hurtbox
	Hurtbox hurt;
	// Speed vector
	Vec2 speed;
	// Position vector (you don't need to use this if you have a sprite)
	Vec2 pos;
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

typedef struct Button {
	char* text;
	Rectangle rect;
	Font font;
	bool clicked;
} Button;

typedef struct Menu {
	// Array of button pointers
	Button** buttons;
	int numButtons;
	char* text;
	Font font;
	Rectangle rect;
} Menu;

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
	// The view rectangle of the camera
	Rectangle rect;
	// Original width and height of camera
	Rectangle orig;
	Rectangle bounds;
	Vec2 scale;
	// Camera is being used for sth.
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