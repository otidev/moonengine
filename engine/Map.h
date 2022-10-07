#ifndef MOON_ENGINE_MAP_H
#define MOON_ENGINE_MAP_H

#include "Include.h"
#include "Physics.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "Camera.h"
#include "cJSON.h"

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

// Returns the root of a json array
cJSON* GetRoot(char* filename);

// Returns a json object.
cJSON* GetObject(cJSON* root, char* layerName, char* objectName);

// Makes a map.
void InitMap(Map* map, char* mapDir, char* filename, int tileWidth, int tileHeight);

// Renders the map that has been created.
void RenderMap(Map* map, SDL_Renderer* renderer);

// Renders a map with an offset.
void RenderMapMod(Map* map, Camera* camera, SDL_Renderer* renderer);

// Returns collision between a map and a rectangle.
bool MapCollision(Map* map, Rectangle rect, int objType, RectSide side);

// Returns collision between a map and a rectangle (using an object group).
bool MapCollisionGroup(Map* map, Rectangle rect, char* objGroup, RectSide side);

// Returns collision between a map and a rectangle (puts tile type in tileType) !CURRENTLY BROKEN!.
bool MapCollisionTile(Map* map, Rectangle rect, int* tileType, RectSide side);

// Get the position of an object.
Vec2 GetObjectPos(char* filename, char* layerName, char* objectName);

// Get a bool property of an object
bool GetObjectPropBool(char* filename, char* layerName, char* objectName, char* propertyName);

#endif