#include "pong.h"

void Pong::onRun()
{
	int type = EXIT;
	int retval;

	onInit();
	while (!quit)
	{
		type = onMenu();
		if (type == EXIT)
			break;
		retval = onCreateGame(type);
		if (retval == EXIT)
			break;
	}
	onCleanup();
}

int Pong::onMenu()
{
	int type = COMPUTER;

	Menu menu = Menu(window);
	type = menu.onRun();
	return type;
}

int Pong::onCreateGame(int type)
{
	int retval;

	if (type == LOCAL)
	{
		Local game(window);
		retval = game.onRun();
	}
	else if (type == REMOTE)
	{
		Remote game(window);
		retval = game.onRun();
	}
	else if (type == COMPUTER)
	{
		Computer game(window);
		retval = game.onRun();
	}
	return (retval);
}

void Pong::onInit()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cerr << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
	else
	{
		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			std::cerr << "Window could not be created! STD_Error: %s\n", SDL_GetError();
	}
}

void Pong::onCleanup()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
