#include "remote.h"

Remote::Remote(SDL_Window *window) :
	Game(window)
{}

int Remote::run()
{
	init_remote_game();
	while (!stop)
	{
		check_event();
		update();
		render();
	}
	handle_disconnection();
	cleanup();
	if (quit_app)
		return (0);
	return (1);

}

void Remote::check_event()
{
	check_start();
	if (start)
	{
		check_sdl_events();
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

void Remote::check_sdl_events()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			conn.send_end_of_game();
			stop = true;
			quit_app = true;
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
	conn.update();
	check_connexion_pause();
	check_connexion_game_over();
	if (conn.is_player1())
		sync_as_player1();
	else
		sync_as_player2();
}

void Remote::sync_as_player1()
{
	conn.sync_ball_racket_score(ball, racket1, racket2);
	if (winner == true)
		conn.send_end_of_game();
	racket2.set_location(conn.get_racket_location());
}

void Remote::sync_as_player2()
{
	conn.sync_racket(racket2);

	racket1.set_location(conn.get_racket_location());
	ball.set_location(conn.get_ball_location());
	ball.set_direction(conn.get_ball_direction());
	racket1.set_score(conn.get_score1());
	racket2.set_score(conn.get_score2());
}

void Remote::check_connexion_pause()
{
	if (conn.is_pause())
		pause == true;
	else
		pause == false;
}

void Remote::check_connexion_game_over()
{
	if (conn.is_game_over())
	{
		stop = true;
		return;
	}
}

void Remote::handle_disconnection()
{
	if (conn.has_player_left() || conn.has_server_stopped() || server_down)
		render_end_of_game();
}

void Remote::render_end_of_game()
{
	stop = false;
	while (!stop)
	{
		renderer.render_end_game(conn, server_down);
		check_event_endgame();
	}
}

void Remote::check_event_endgame()
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

void Remote::cleanup()
{
	Message eog("EOG", "");
	conn.send_message(eog);
	conn.cleanup();
	renderer.cleanup();
}
