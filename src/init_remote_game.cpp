#include "remote.h"

void Remote::init_remote_game()
{
	set_player_name();
	if (!init_connexion())
		return;
	setup_game();
}

void Remote::set_player_name()
{
	std::string message;
	SDL_StartTextInput();

	while (!stop)
	{
		message = "Enter your name: " + name;
		renderer.clear_screen();
		renderer.render_text(message, {SCREEN_WIDTH / 2, SCREEN_HEIGHT /2});
		renderer.render_now();
		check_event_setname();
	}
	if (!back_to_menu)
		stop = false;
	SDL_StopTextInput();
}

void Remote::check_event_setname()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quit_app = true;
			back_to_menu = true;
			stop = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_BACKSPACE && (name.size() > 0))
			{
				name.pop_back();
			}
			else if (event.key.keysym.sym == SDLK_RETURN && (name.size() > 0))
			{
				stop = true;
				SDL_StopTextInput();
				return;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_StopTextInput();
				back_to_menu = true;
				stop = true;
				return;
			}
		}
		else if (event.type == SDL_QUIT)
		{
			SDL_StopTextInput();
			stop = true;
			quit_app = true;
			return;
		}
		else if (event.type == SDL_TEXTINPUT)
		{
			name += event.text.text;
		}
	}
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
		check_event_waiting_room();
		setup_if_ready();
		render_waiting_room();
	}
	if (!back_to_menu)
		stop = false;
}

void Remote::check_event_waiting_room()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			stop = true;
			quit_app = true;
			back_to_menu = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				stop = true;
				back_to_menu = true;
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

void Remote::setup_if_ready()
{
	if (conn.is_setup_ready() && !setup)
	{
		if (conn.check_flags(PLAYER1))
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

void Remote::render_waiting_room()
{
	renderer.render_waiting_room(conn, racket1, racket2, name);
}
