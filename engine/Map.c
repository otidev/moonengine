#include "Map.h"

cJSON* GetRoot(char* filename) {
	// Load file
	int fileSize;

	FILE* file = fopen(filename, "rb");

	// Getting file size
	fseek(file, 0l, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0l, SEEK_SET);
	
	// Put it in a buffer.
	char fileBuf[fileSize];
	memset(fileBuf, 0, fileSize);
	fread(fileBuf, sizeof(char), fileSize, file);

	fclose(file);

	// Start parsing!
	cJSON* root = cJSON_Parse(fileBuf);
	return root;
}

static void ParseTileset(Tileset* tileset, char* tsDir, char* filename) {
	char fullFilename[1024];
	strcpy(fullFilename, tsDir);
	strcat(fullFilename, filename);
	cJSON* root = GetRoot(fullFilename);

	// Load texture
	char srcFilename[1024];
	strcpy(srcFilename, tsDir);
	strcat(srcFilename, cJSON_GetObjectItem(root, "image")->valuestring);
	tileset->texture = LoadTexture(srcFilename);

	// Get last GID
	tileset->lastgid = cJSON_GetObjectItem(root, "tilecount")->valueint + tileset->firstgid - 1;
	cJSON* tiles = cJSON_GetObjectItem(root, "tiles");
	int tileCount = cJSON_GetArraySize(tiles);

	for (int i = 0; i < tileCount; i++) {
		cJSON* tile = cJSON_GetArrayItem(tiles, i);
		cJSON_HasObjectItem(tile, "type") ? tileset->tileGroup[i] = cJSON_GetObjectItem(tile, "type")->valuestring : 0;
	}

}

void InitMap(Map* map, char* mapDir, char* filename, int tileWidth, int tileHeight) {
	char fullFilename[1024];
	strcpy(fullFilename, mapDir);
	strcat(fullFilename, filename);
	for (int i = 0; i < strlen(fullFilename); i++)
		map->filename[i] = fullFilename[i];
	cJSON* root = GetRoot(fullFilename);

	const char *errorPtr = cJSON_GetErrorPtr();
	if (errorPtr != NULL) {
		fprintf(stderr, "Error at %s", errorPtr);
	}
	
	// Get tile width and height
	map->tileWidth = tileWidth;
	map->tileHeight = tileHeight;

	// Get width and height
	map->width = cJSON_GetObjectItem(root, "width")->valueint;
	map->height = cJSON_GetObjectItem(root, "height")->valueint;

	if (map->tileWidth != cJSON_GetObjectItem(root, "tilewidth")->valueint || map->tileHeight != cJSON_GetObjectItem(root, "tilewidth")->valueint)
		fprintf(stderr, "\033[1mNote\033[0m: Tile width/height not equally defined in file!");

	// Layers
	cJSON* layers = cJSON_GetObjectItem(root, "layers");
	int layerCount = cJSON_GetArraySize(layers);
	
	// Loop for each layer
	for (int i = 0; i < layerCount; i++) {
		cJSON* layer = cJSON_GetArrayItem(layers, i);
		cJSON* data = cJSON_GetObjectItem(layer, "data");

		// Foreground or Background
		if (cJSON_GetObjectItem(layer, "name")->valuestring[0] == 'f') {
			for (int y = 0; y < map->height; y++) {
				for (int x = 0; x < map->width; x++) {
					map->mapFg[y][x] = cJSON_GetArrayItem(data, y * map->width + x)->valuedouble;
				}
			}
		} else if (cJSON_GetObjectItem(layer, "name")->valuestring[0] == 'b') {
			for (int y = 0; y < map->height; y++) {
				for (int x = 0; x < map->width; x++) {
					map->mapBg[y][x] = cJSON_GetArrayItem(data, y * map->width + x)->valuedouble;
				}
			}		
		} else {
			fprintf(stderr, "\033[1mNote\033[0m: Layer '%s' is not foreground or background!\n", cJSON_GetObjectItem(layer, "name")->valuestring);
		}
	}

	// Tileset
	cJSON* tilesets = cJSON_GetObjectItem(root, "tilesets");
	int tilesetCount = cJSON_GetArraySize(tilesets);
	map->numTilesets = tilesetCount;

	for (int i = 0; i < tilesetCount; i++) {
		cJSON* tileset = cJSON_GetArrayItem(tilesets, i);
		map->tileset[i].firstgid = cJSON_GetObjectItem(tileset, "firstgid")->valueint;
		ParseTileset(&map->tileset[i], mapDir, cJSON_GetObjectItem(tileset, "source")->valuestring);
	}

	cJSON_Delete(root);
}

cJSON* GetObject(cJSON* root, char* layerName, char* objectName) {
	const char *errorPtr = cJSON_GetErrorPtr();
	if (errorPtr != NULL) {
		fprintf(stderr, "\033[1Error at:\033[0 %s", errorPtr);
	}

	// Get object
	cJSON* layerGroup = cJSON_GetObjectItem(root, "layers");
	cJSON* layer;
	int layerCount = cJSON_GetArraySize(layerGroup);

	bool breakLoop;
	int i;

	for (i = 0; i < layerCount; i++) {
		if (strcmp(cJSON_GetObjectItem(cJSON_GetArrayItem(layerGroup, i), "name")->valuestring, layerName) == 0 && strcmp(cJSON_GetObjectItem(cJSON_GetArrayItem(layerGroup, i), "type")->valuestring, "objectgroup") == 0) {
			breakLoop = true;
			break;
		}
	}
	
	// If we didn't continue the loop automatically
	if (breakLoop == false) {
		cJSON_Delete(root);
		return NULL;
	}

	// Set layer, group and count for group
	layer = cJSON_GetArrayItem(layerGroup, i);
	cJSON* objectGroup = cJSON_GetObjectItem(layer, "objects");
	int objectCount = cJSON_GetArraySize(objectGroup);

	for (int i = 0; i < objectCount; i++) {
		cJSON* object = cJSON_GetArrayItem(objectGroup, i);
		if (strcmp(cJSON_GetObjectItem(object, "name")->valuestring, objectName) == 0) {
			return object;
		}
	}

	return 0;
}

Vec2 GetObjectPos(char* filename, char* layerName, char* objectName) {
	cJSON* root = GetRoot(filename);
	cJSON* object = GetObject(root, layerName, objectName);
	Vec2 entPos;

	entPos.x = cJSON_GetObjectItem(object, "x")->valuedouble;
	entPos.y = cJSON_GetObjectItem(object, "y")->valuedouble;

	cJSON_Delete(root);
	return entPos;
}

bool GetObjectPropBool(char* filename, char* layerName, char* objectName, char* propertyName) {
	cJSON* root = GetRoot(filename);
	cJSON* object = GetObject(root, layerName, objectName);
	bool objectPropBool;

	cJSON* objectProps = cJSON_GetObjectItem(object, "properties");

	for (int i = 0; i < cJSON_GetArraySize(objectProps); i++) {
		cJSON* objectProp = cJSON_GetArrayItem(objectProps, i);
		if (
		strcmp(cJSON_GetObjectItem(objectProp, "name")->valuestring, propertyName) == 0
		&& 
		strcmp(cJSON_GetObjectItem(objectProp, "type")->valuestring, "bool")
		) {
			objectPropBool = cJSON_IsTrue(cJSON_GetObjectItem(objectProp, "value"));
			}
	}


	cJSON_Delete(root);
	return objectPropBool;
}

static void RecordType(uint32_t tileType, uint32_t* flippedH, uint32_t* flippedV, uint32_t* rotated, Rectangle *rect, Map* map) {
	// Get texture width and height
	int texWidth, texHeight;
	int firstgid = 0;
	for (int i = 0; i < map->numTilesets; i++) {
		if (tileType <= map->tileset[i].lastgid && tileType >= map->tileset[i].firstgid) {
			firstgid = map->tileset[i].firstgid;
			map->mapRenderTexture = map->tileset[i].texture;
		}
	}
	SDL_QueryTexture(map->mapRenderTexture, NULL, NULL, &texWidth, &texHeight);

	// Get tiles per row and column
	int tileLengthX = texWidth / map->tileWidth;
	int tileLengthY = texHeight / map->tileHeight;
	// Get number of tiles
	int tileCount = tileLengthX * tileLengthY;
	int i = firstgid, y = 0, x = 0;

	uint32_t parse = tileType;

	bool rot = (parse >> 29) & 1;

	if (rot) {
		*rotated = 270; // I don't know why, I think it's because of rotating left and flipping?
		*flippedV = SDL_FLIP_VERTICAL;
	}

	bool flipH = (parse >> 31) & 1;

	if (flipH)
		*flippedH = SDL_FLIP_HORIZONTAL;

	bool flipV = (parse >> 30) & 1;

	if (flipV) {
		if (*flippedV)
			*flippedV = 0;
		else
			*flippedV = SDL_FLIP_VERTICAL;
	}
	
	parse &= ~(0x80000000 | 0x40000000 | 0x20000000);

	// If less/more than is offered, rect is nulled
	if (parse <= 0 || parse > map->tileset[map->numTilesets - 1].lastgid) {
		*rect = (Rectangle){0};
		return;
	}

	while (i < parse) {
		i++;
		x++;
		if (x == tileLengthX) {
			y++;
			x = 0;
		}
	}

	*rect = (Rectangle){map->tileWidth * x, map->tileHeight * y, map->tileWidth, map->tileHeight};
	return;
}

void RenderMap(Map* map, SDL_Renderer* renderer) {
	RenderMapMod(map, &(Camera){0}, renderer);
}

void RenderMapMod(Map* map, Camera* camera, SDL_Renderer* renderer) {
	uint32_t tileType = 0;
	Rectangle src;
	Rectangle dst;

	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			uint32_t flippedH = 0;
			uint32_t flippedY = 0;
			uint32_t rotated = 0;
			dst = (Rectangle){x * map->tileWidth, y * map->tileHeight, map->tileWidth, map->tileHeight};
			if (RectangleInCamera(camera, dst)) {
				// Recording foreground
				tileType = map->mapFg[y][x];
				RecordType(tileType, &flippedH, &flippedY, &rotated, &src, map);
				DrawTextureEx(map->mapRenderTexture, &src, &(Rectangle){dst.x - camera->rect.x, dst.y - camera->rect.y, dst.w, dst.h}, rotated, &(SDL_Point){map->tileWidth / 2, map->tileHeight / 2}, flippedH | flippedY, renderer);

				// Recording background
				tileType = map->mapBg[y][x];
				RecordType(tileType, &flippedH, &flippedY, &rotated, &src, map);
				DrawTextureEx(map->mapRenderTexture, &src, &(Rectangle){dst.x - camera->rect.x, dst.y - camera->rect.y, dst.w, dst.h}, rotated, &(SDL_Point){map->tileWidth / 2, map->tileHeight / 2}, flippedH | flippedY, renderer);
			}
		}
	}
}

bool MapCollision(Map* map, Rectangle rect, int objType, RectSide side) {
	int currentTile;

	// Transfer foreground map to collision map
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			map->mapColl[y][x] = map->mapFg[y][x] & ~(0x80000000 | 0x40000000 | 0x20000000);
		}
	}


	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			// Assign current tile as the collision tile
			currentTile = map->mapColl[y][x];
			if (currentTile != 0 && objType == currentTile) {
				// Change collision rect
				map->collisionRect = (Rectangle){x * map->tileWidth, y * map->tileHeight, map->tileWidth, map->tileHeight};
				if (side == NONE) {
					if (RectangleCollide(rect, map->collisionRect))
						return true;
				} else {
					if (RectangleSideCollide(rect, map->collisionRect, side))
						return true;
				}
			}
		}
	}

	return false;
}

bool MapCollisionGroup(Map* map, Rectangle rect, char* objGroup, RectSide side) {
	int currentTile;

	// Transfer foreground map to collision map
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			map->mapColl[y][x] = map->mapFg[y][x] & ~(0x80000000 | 0x40000000 | 0x20000000);
		}
	}


	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			// Assign current tile as the collision tile
			currentTile = map->mapColl[y][x];
			char* objectData;
			for (int i = 0; i < map->numTilesets; i++) {
				if (currentTile <= map->tileset[i].lastgid && currentTile >= map->tileset[i].firstgid) {
					objectData = map->tileset[i].tileGroup[currentTile - map->tileset[i].firstgid];
					break;
				}
			}
			if (currentTile != 0 && (strcmp(objectData, objGroup) == 0)) {
				// Change collision rect
				map->collisionRect = (Rectangle){x * map->tileWidth, y * map->tileHeight, map->tileWidth, map->tileHeight};
				if (side == NONE) {
					if (RectangleCollide(rect, map->collisionRect))
						return true;
				} else {
					if (RectangleSideCollide(map->collisionRect, rect, side))
						return true;
				}
			}
		}
	}

	return false;
}

bool MapCollisionTile(Map* map, Rectangle rect, int* tileType, RectSide side) {
	int currentTile;

	// Transfer foreground map to collision map
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			map->mapColl[y][x] = map->mapFg[y][x] & ~(0x80000000 | 0x40000000 | 0x20000000);
		}
	}


	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			// Assign current tile as the collision tile
			currentTile = map->mapColl[y][x];
			if (currentTile != 0) {
				// Change collision rect
				map->collisionRect = (Rectangle){x * map->tileWidth, y * map->tileHeight, map->tileWidth, map->tileHeight};
				if (side == NONE) {
					if (RectangleCollide(rect, map->collisionRect)) {
						tileType ? *tileType = map->mapColl[y][x] : 0;
						return true;
					}
				} else {
					if (RectangleSideCollide(rect, map->collisionRect, side)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}