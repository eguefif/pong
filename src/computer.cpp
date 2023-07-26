#include "local.h"

Computer::Computer(SDL_Window *aWindow)
{
	window = aWindow;
}

void Computer::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}
