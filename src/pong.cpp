#include "pong.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Pong::Pong()
{}


void Pong::onRun()
{
	int type = EXIT;

	onInit();
	while (!quit)
	{
		onEvent();
		type = onMenu();
		if (type == EXIT)
			break;
		onCreateGame(type);
	}
	onCleanup();
}

int Pong::onMenu()
{
	return 1;
}

void Pong::onCreateGame(int type)
{
	game = Game(type, window);
	game.onRun();
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

void Pong::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
		if (event.type == SDL_QUIT)
			quit = true;
}
