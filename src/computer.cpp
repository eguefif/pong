#include "computer.h"

Computer::Computer(SDL_Window *window) :
	Game(window)
{
}

void Computer::onEvent()
{
	check_events();
	check_keys();
	check_ia();
}

void Computer::check_events()
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

void Computer::check_keys()
{
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP])
			racket2.up();
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
			racket2.down();
}

void Computer::check_ia()
{
	int direction = ia.where_to_go(ball, racket1);

	switch(direction)
	{
		case 0: break;
		case 1: racket1.up();
				break;
		case 2: racket1.down();
				break;
	}
}
