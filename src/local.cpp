#include "local.h"

Local::Local(SDL_Window *aWindow)
{
	window = aWindow;
}

void Local::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}
