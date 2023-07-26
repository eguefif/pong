#include "local.h"

Remote::Remote(SDL_Window *aWindow) :
	window(aWindow)
{}

void Remote::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}
