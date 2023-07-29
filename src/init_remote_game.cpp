#include "remote.h"

void Remote::init_remote_game()
{
	set_name();
	if (!init_connexion())
		return;
	setup_game();
}

void Remote::set_name()
{
	std::string message;
	SDL_StartTextInput();

	while (!stop)
	{
		message = "Enter your name: " + name;
		renderer.clear_screen();
		renderer.render_text(message, {SCREEN_WIDTH / 2, SCREEN_HEIGHT /2});
		renderer.render_now();
		SDL_Event ev;
		memset(&ev, 0, sizeof(ev));
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_KEYDOWN)
			{
				if (ev.key.keysym.sym == SDLK_BACKSPACE && (name.size() > 0))
				{
					name.pop_back();
				}
				else if (ev.key.keysym.sym == SDLK_RETURN && (name.size() > 0))
				{
					stop = false;
					SDL_StopTextInput();
					return;
				}
				else if (ev.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_StopTextInput();
					stop = true;
					return;
				}
			}
			else if (ev.type == SDL_QUIT)
			{
				SDL_StopTextInput();
				stop = true;
				quit = true;
				return;
			}
			else if (ev.type == SDL_TEXTINPUT)
			{
				name += ev.text.text;
			}
		}
	}
	stop = false;
	SDL_StopTextInput();
}

bool Remote::init_connexion()
{
	if (!conn.connect_to_server())
	{
		server_down = true;
		stop = true;
		return (false);
	}
	return (true);
}

void Remote::setup_game()
{
	Message message_name("name", name);
	conn.send_message(message_name);
	while (!stop)
	{
		setup_if_ready();
		render_waiting_room();
		check_event_waiting_room();
	}
	if (previous_screen != true)
		stop = false;
}

void Remote::setup_if_ready()
{
	if (conn.is_setup_done() && !setup)
	{
		if (conn.is_player1())
		{
			racket1.set_name(name);
			racket2.set_name(conn.get_foe_name());
		}
		else
		{
			racket2.set_name(name);
			racket1.set_name(conn.get_foe_name());
		}
		ball.set_direction(conn.get_ball_direction());
		setup = true;
	}
}

void Remote::check_event_waiting_room()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			stop = true;
			quit = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				stop = true;
				previous_screen = true;
			}
			else if (event.key.keysym.sym == SDLK_RETURN && setup)
			{
				Message ready_message("ready");
				conn.send_message(ready_message);
				stop = true;
			}
		}
	}
}

void Remote::render_waiting_room()
{

	if (conn.is_player1() && !conn.is_setup_done())
	{
		renderer.clear_screen();
		renderer.render_text("Pong remote", {SCREEN_WIDTH / 2 - 5, 50});
		std::string line1 = "Waiting for another player";
		renderer.render_text(line1, {SCREEN_WIDTH / 2 -(int) line1.size()/2, 100});
		std::string line2 = "Player 1: " + name;
		renderer.render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
		renderer.render_now();
	}
	else
	{
		std::string line1 = "The game is full. Push return when ready.";
		std::string line2 = "Player 1: " + racket1.get_name();
		std::string line3 = "Player 2: " + racket2.get_name();
		renderer.clear_screen();
		renderer.render_text(line1, {SCREEN_WIDTH / 2 - (int) line1.size()/2, 100});
		renderer.render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
		renderer.render_text(line3, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 200});
		renderer.render_now();
	}
}

