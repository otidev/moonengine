#ifndef MOON_ENGINE_HBOX_H
#define MOON_ENGINE_HBOX_H

#include "Include.h"

// Datatypes found in the file
typedef struct KBN_Header {
	uint8_t magicNum[4];
	uint8_t numBoxes;
} __attribute__((packed)) KBN_Header;

typedef struct KBN_Box {
	uint8_t indentifier;
	uint32_t framePos;
	
	// Box dimensions
	int x;
	int y;
	int w;
	int h;
	
	// Box colours
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} __attribute__((packed)) KBN_Box;

// Loads a Kuben file into an HBox (Hitbox/Hurtbox)
void LoadHBox(Hitbox* HBox, uint8_t boxIdentifier, char* filename);

#endif
