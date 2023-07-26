#include "local.h"

Remote::Remote(SDL_Window *window) : Game(window)
{}

void Remote::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}
