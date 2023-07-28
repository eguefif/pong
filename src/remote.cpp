#include "remote.h"

Remote::Remote(SDL_Window *window) : Game(window)
{
}

int Remote::onRun()
{
	init_remote_game();
	stop = false;
	while (!conn.waiting_to_start() && !stop)
		check_event_waiting_room();
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

void Remote::init_remote_game()
{
	set_name();
	init_connexion();
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
		while (SDL_PollEvent(&ev))
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
	SDL_StopTextInput();
	stop = false;
}

void Remote::init_connexion()
{
	if (!conn.connect_to_server())
		stop = true;
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
	stop = false;
}

void Remote::setup_if_ready()
{
	if (conn.is_setup_done())
	{
		std::cout << "DONE ? " << conn.is_setup_done() << std::endl;
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
		stop = true;
	}
}

void Remote::check_event_waiting_room()
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		if (event.type == SDL_QUIT)
		{
			stop = true;
			quit = true;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				stop = true;
			else if (event.key.keysym.sym == SDLK_SPACE && (conn.is_setup_done()))
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
		std::string line1 = "The game is full. Push space when ready.";
		std::string line2 = "Player 1: " + racket1.get_name();
		std::string line3 = "Player 2: " + racket2.get_name();
		renderer.clear_screen();
		renderer.render_text(line1, {SCREEN_WIDTH / 2 - (int) line1.size()/2, 100});
		renderer.render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
		renderer.render_text(line3, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 200});
		renderer.render_now();
	}
}

void Remote::onEvent()
{
	check_events();
	check_keys();
}

void Remote::check_events()
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

void Remote::check_keys()
{
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP])
			racket2.up();
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
			racket2.down();
	if (currentKeyStates[SDL_SCANCODE_A])
			racket1.down();
	else if (currentKeyStates[SDL_SCANCODE_Q])
			racket1.up();
}
