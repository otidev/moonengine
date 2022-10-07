#include "MoonEngine.h"
int main() {
	Window window;
	InitWin(&window, 1024, 720, "Moon");
	while (WindowIsOpen(&window, 60)) {
		printf("Window open, running at 60 fps!");
	}
	End(window);
	return 0;
}