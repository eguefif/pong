#include "local.h"

Local::Local(SDL_Window *window) : Game(window)
{}

void Local::onEvent()
{
	check_events();
	check_keys();
	check_scorer();
}

void Local::check_events()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			stop = true;
			quit = true;
		}
		else if(event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: stop = true;
								  break;
				case SDLK_SPACE: switch_pause();
								 break;
			}
		}
	}
}

void Local::check_keys()
{
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP])
			racket2.up();
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
			racket2.down();
	if (currentKeyStates[SDL_SCANCODE_A])
			racket1.down();
	else if (currentKeyStates[SDL_SCANCODE_Q])
			racket1.up();
}

void Local::check_scorer()
{
}
