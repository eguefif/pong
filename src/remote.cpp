#include "remote.h"

Remote::Remote(SDL_Window *window) :
	Game(window)
{}

int Remote::onRun()
{
	init_remote_game();
	while (!stop)
	{
		onEvent();
		onUpdate();
		onRender();
	}
	if (conn.has_player_left() || conn.has_server_stopped() || server_down)
		render_end_of_game();
	onCleanup();
	if (quit)
		return (3);
	return (0);

}

void Remote::onEvent()
{
	check_start();
	if (start)
	{
		check_events();
		check_keys();
		update_connexion();
	}
}

void Remote::check_start()
{
	if (conn.waiting_to_start() && !start)
	{
		start = true;
		pause = false;
	}
}

void Remote::check_events()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			conn.send_end_of_game();
			stop = true;
			quit = true;
		}
		else if(event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:	stop = true;
									conn.send_end_of_game();
								  break;
				case SDLK_SPACE:	switch_pause();
									conn.send_pause_status(pause);
								 break;
			}
		}
	}
}

void Remote::check_keys()
{
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

	if (!conn.is_player1())
	{
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			racket2.up();
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			racket2.down();
		}
	}
	else
	{
		if (currentKeyStates[SDL_SCANCODE_A])
		{
			racket1.down();
		}
		else if (currentKeyStates[SDL_SCANCODE_Q])
		{
			racket1.up();
		}
	}
}

void Remote::update_connexion()
{
	t_coord location;

	conn.update();
	if (conn.is_pause())
		pause == true;
	else
		pause == false;
	if (conn.is_game_over())
	{
		stop = true;
		return;
	}
	if (conn.is_player1())
	{
		conn.sync_ball_racket_score(ball, racket1, racket2);
		if (winner == true)
			conn.send_end_of_game();
		racket2.set_location(conn.get_racket_location());
	}
	else
	{
		conn.sync_racket(racket2);
		racket1.set_location(conn.get_racket_location());
		location = conn.get_ball_location();
		ball.set_location(location);
		ball.set_direction(conn.get_ball_direction());
		racket1.set_score(conn.get_score1());
		racket2.set_score(conn.get_score2());
	}
}

void Remote::onCleanup()
{
	conn.cleanup();
	renderer.cleanup();
}

void Remote::render_end_of_game()
{
	stop = false;
	while (!stop)
	{
		if (conn.has_player_left())
			renderer.render_text("Your opponent has left.", {SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT / 2});
		if (server_down = true)
			renderer.render_text("Server down", {SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT / 2 + 100});
		else if (conn.has_server_stopped())
			renderer.render_text("The server has shutdown.", {SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT / 2});

		renderer.render_now();
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
}

