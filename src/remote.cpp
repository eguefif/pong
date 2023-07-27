#include "remote.h"

Remote::Remote(SDL_Window *window) : Game(window)
{
}

int Remote::onRun()
{
	init_remote_game();
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

void Remote::setup_game()
{
	Message message_name("name", name);
	SDL_Event ev;

	stream.send_message(message_name);

	while (!stop || is_init_done())
	{
		render_waiting_room();
		stream.read_message();
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
				else if (event.key.keysym.sym == SDLK_SPACE && (init_flag & NAME))
				{
					init_flag &= READY;
					Message ready_message("ready");
					stream.send_message(ready_message);
				}
			}
		}
		for (auto message = stream.messages.begin(); message != stream.messages.end(); ++message)
		{
			if (message->get_command() == "waiting")
			{
				racket1.set_name(name);
				stream.messages.erase(message);
				break;
			}
			else if (message->get_command() == "name")
			{
				racket2.set_name(message->get_content());
				stream.messages.erase(message);
				init_flag &= NAME;
				break;
			}
			else if(message->get_command() == "ball")
			{
				ball.set_direction(atoi(message->get_content().c_str()));
				init_flag &= BALL;
			}
		}
	}
}

void Remote::render_waiting_room()
{
	renderer.clear_screen();
	renderer.render_text("Pong remote", {SCREEN_WIDTH / 2 - 5, 50});

	if (!(init_flag & NAME))
	{
		std::string waiting_line = "Waiting for another player";
		renderer.render_text(waiting_line, {SCREEN_WIDTH / 2 -(int) waiting_line.size()/2, 100});
	}
	else if((init_flag & NAME) && (
	{
		std::string line1 = "The game is full. Push space when ready.";
		std::string line2 = "Player 1: " + racket1.get_name();
		std::string line3 = "Player 2: " + racket2.get_name();
		renderer.render_text(line1, {SCREEN_WIDTH / 2 - (int) line1.size()/2, 100});
		renderer.render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
		renderer.render_text(line3, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 175});
	}
	if ((
			renderer.render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
			std::string line2 = "Player 1: " + name;
}

bool Remote::is_init_done()
{
	return ((init_flag & NAME) && (init_flag & BALL) && (init_flag & READY));
}

void Remote::init_connexion()
{
	int fd;
	struct sockaddr_in add;
	int opt = 2;

	memset(&add, 0, sizeof(add));
	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	add.sin_family = AF_INET;
	add.sin_port = htons(PORT);
	add.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(add.sin_zero, 0, sizeof(add.sin_zero));
	if (connect(fd, (struct sockaddr *) &add, sizeof(add)) < 0)
	{
		std::cerr << "Impossible to connect to server " << errno << std::endl;
		stop = true;
	}
	TCP_Stream astream(fd, &add);
	stream = astream;
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
