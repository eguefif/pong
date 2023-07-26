#include "pong.h"

Game::Game(SDL_Window *awindow) :
	window(awindow)
{
	Renderer arenderer(awindow);
	renderer = arenderer;
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
	renderer.render_scene();
}

void Game::onUpdate()
{
	renderer.update_scene(ball);
}

void Game::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
}
