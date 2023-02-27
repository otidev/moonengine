#include "HBox.h"

void LoadHBox(Hitbox* HBox, uint8_t boxIdentifier, char* filename) {
    FILE* file = fopen(filename, "rb");

	fseek(file, 0l, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0l, SEEK_SET);
	
	char fileBuf[fileSize];
	int locationInFile = 0;
	fread(fileBuf, sizeof(char), fileSize, file);

	if (fileSize <= 0) {
		fprintf(stderr, "Error: The file \"%s\" doesn't exist", filename);
		return;
	}

	KBN_Header header;
	memcpy(&header, fileBuf + locationInFile, sizeof(KBN_Header));
	locationInFile += sizeof(KBN_Header);

	if (
		!(header.magicNum[0] == 'K' 
		&& header.magicNum[1] == 'U'
		&& header.magicNum[2] == 0x17
		&& header.magicNum[3] == 0x1)
	) {
		fprintf(stderr, "Error: The file %s is not a .kuben file", filename);
		return;
	}
	

	KBN_Box box;
	memset(&box, 0, sizeof(KBN_Box));
	memcpy(&box, fileBuf + locationInFile + (sizeof(KBN_Box) * boxIdentifier), sizeof(KBN_Box));

	printf("%f %f %f %f", (float)box.x, (float)box.y, (float)box.w, (float)box.h);

	*HBox = (Hitbox) {
		(Vec2){(float)box.x, (float)box.y},
		false,
		(Rectangle){(float)box.x, (float)box.y, (float)box.w, (float)box.h}
	};
}
