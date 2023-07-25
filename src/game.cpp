#include "pong.h"

Game::Game(SDL_Window *aWindow)
{
	//Racket racket1(LEFT);
	//Racket racket2(RIGHT);
	//Ball ball();
	window = aWindow;
}

void Game::onRun()
{
	while (!quit)
	{
		onEvent();
		onUpdate();
		onRender();
	}
}

void Game::onRender() const
{
}

void Game::onUpdate()
{
}

void Game::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}
