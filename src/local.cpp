#include "local.h"

Local::Local(SDL_Window *window) : Game(window)
{}

void Local::check_event()
{
	check_sdl_events();
	check_keys();
}

void Local::check_sdl_events()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			stop = true;
			quit_app = true;
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
