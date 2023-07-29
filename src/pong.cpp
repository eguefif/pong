#include "pong.h"

void Pong::onRun()
{
	int retval;

	init_sdl_and_window();
	while (game_type != EXIT)
	{
		run_menu();
		run_game();
	}
	cleanup();
}

void Pong::init_sdl_and_window()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cerr << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
	else
	{
		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			std::cerr << "Window could not be created! STD_Error: %s\n", SDL_GetError();
	}
}

void Pong::run_menu()
{
	Menu menu = Menu(window);
	game_type = menu.onRun();
}

void Pong::run_game()
{
	int retval;

	if (game_type == LOCAL)
	{
		Local game(window);
		retval = game.onRun();
	}
	else if (game_type == REMOTE)
	{
		Remote game(window);
		retval = game.onRun();
	}
	else if (game_type == COMPUTER)
	{
		Computer game(window);
		retval = game.onRun();
	}

	if(retval == EXIT)
		game_type = EXIT;
}

void Pong::cleanup()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
