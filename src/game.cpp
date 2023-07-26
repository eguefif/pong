#include "pong.h"

Game::Game()
{
	t_coord location;
	location.x = SCREEN_WIDTH / 2;
	location.y = SCREEN_HEIGHT / 2;
	Ball aball(location);
	ball = aball;
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
