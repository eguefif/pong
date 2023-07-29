#include "game.h"

Game::Game(SDL_Window *awindow) :
	window(awindow),
	racket1(0),
	racket2(1),
	renderer(awindow)
{}

int Game::onRun()
{
	while (!stop)
	{
		onEvent();
		onUpdate();
		onRender();
	}
	onCleanup();
	if (quit)
		return (3);
	return (0);
}

void Game::onRender() const
{
	if (winner)
		renderer.render_winner(winner_name);
	else
		renderer.render_scene(ball, racket1, racket2);
}

void Game::onUpdate()
{
	racket1.move();
	racket2.move();
	if (!pause && !winner)
	{
		ball.move(racket1, racket2);
		if (ball.is_score())
		{
			if (ball.get_scorer() == 0)
				racket2.update_score();
			else if(ball.get_scorer() == 1)
				racket1.update_score();
			if (racket2.get_score() == 5 || racket1.get_score() == 5)
				{
					pause = true;
					winner = true;
					set_winner_name();
				}
			else
				{
					reset();
					pause = true;
				}
		}
	}
}

void Game::onEvent()
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

void Game::switch_pause()
{
	if (pause == true)
		pause = false;
	else
		pause = true;
}

void Game::onCleanup()
{
	renderer.cleanup();
}

void Game::reset()
{
	t_coord loc = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	ball.set_location(loc);
}

void Game::set_winner_name()
{
	if (racket1.get_score() == 5)
		winner_name = racket1.get_name();
	else if (racket2.get_score() == 5)
		winner_name = racket2.get_name();
}
