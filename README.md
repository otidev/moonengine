# MoonEngine - An engine used to make (semi-)powerful games.
MoonEngine (or Moon) is a 70KB game engine/framework that I've (oti) been working on, that's quite modular with help of backends (i.e. SDL2 and derivs).

**NOTE**: Because this engine is under rapid development, this is Alpha (expect breaking changes!).

Some features of the engine include:

- `Camera` - A camera system
- `Font` - A font rendering system
- `Input` - An input handler
- `Map` - A Tiled renderer and parser
- `Sound` - A sound system

...and more!

## Questions (and stuff)

[Go here!](FAQ.md)

## Example
Plugging these 10 lines of code into a working environment will give a blank window:
```
#include "MoonEngine.h"
int main() {
	Window window;
	InitWindow(&window, 1024, 720, "Moon");
	while (WindowIsOpen(60)) {
		printf("Window open, running at 60 fps!\n");
	}
	End(window);
	return 0;
}
```

This is the same code in "main.c".

## Compilation
To compile Moon, you need:

- SDL2_ttf
- SDL2_image
- SDL2
- SDL2_mixer
- SDL2_gpu
- SDL2main (on Windows)

### If you're running Windows
Extract all of the files from the Github repos, them leave them as is. You'll need the original folders in the CMake.

## Photos
![Photo of Blit, my game](Blit.png)