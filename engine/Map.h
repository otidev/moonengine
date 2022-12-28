#ifndef MOON_ENGINE_MAP_H
#define MOON_ENGINE_MAP_H

#include "Include.h"
#include "Physics.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "Camera.h"
#include "cJSON.h"

// Returns the root of a json array
cJSON* GetRoot(char* filename);

// Returns a json object.
cJSON* GetObject(cJSON* root, char* layerName, char* objectName);

// Makes a map.
void InitMap(Map* map, char* mapDir, char* filename, int tileWidth, int tileHeight);

// Renders the map that has been created.
void RenderMap(Map* map);

// Renders a map with an offset.
void RenderMapMod(Map* map, Camera* camera);

// Returns collision between a map and a rectangle.
bool MapCollision(Map* map, Rectangle rect, int objType, RectSide side);

// Returns collision between a map and a rectangle (using an object group).
bool MapCollisionGroup(Map* map, Rectangle rect, char* objGroup, RectSide side);

// Returns collision between a map and a rectangle (puts tile type in tileType) !CURRENTLY BROKEN!.
bool MapCollisionTile(Map* map, Rectangle rect, int* tileType, RectSide side);

// Get the position of an object.
Vec2 GetObjectPos(char* filename, char* layerName, char* objectName);

// Get a bool-type property of an object
bool GetObjectPropBool(char* filename, char* layerName, char* objectName, char* propertyName);

// Get a string-type property of an object
char* GetObjectPropStr(char* filename, char* layerName, char* objectName, char* propertyName);

#endif