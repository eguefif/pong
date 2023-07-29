#include "connexion.h"

Connexion::Connexion(std::string add, int aport) :
	address(add), port(aport)
{}

bool Connexion::connect_to_server()
{
	int fd;
	struct sockaddr_in add;
	int opt = 2;

	memset(&add, 0, sizeof(add));
	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	add.sin_family = AF_INET;
	add.sin_port = htons(port);
	add.sin_addr.s_addr = inet_addr(address.c_str());
	memset(add.sin_zero, 0, sizeof(add.sin_zero));
	if (connect(fd, (struct sockaddr *) &add, sizeof(add)) < 0)
	{
		std::cerr << "Impossible to connect to server " << errno << std::endl;
		return (false);
	}
	to_non_blocking(fd);
	TCP_Stream astream(fd, &add);
	stream = astream;
	return (true);
}

bool Connexion::is_setup_ready()
{
	check_message();
	return (((init_flag & NAME) == NAME) && ((init_flag & BALL) == BALL) && ((init_flag & FULL) == FULL));
}

bool Connexion::is_player1()
{
	return (init_flag & WAITING);
}

void Connexion::check_message()
{
	stream.read_message();
	for (auto message =  stream.messages.begin(); message != stream.messages.end(); ++message)
	{
		if (message->get_command() == "waiting")
		{
			init_flag |= WAITING;
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "joining")
		{
			init_flag |= JOINING;
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "ball")
		{
			init_flag |= BALL;
			ball_direction = atoi(message->get_content().c_str());
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "name")
		{
			init_flag |= NAME;
			foe_name = message->get_content();
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "ready")
		{
			init_flag |= READY;
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "full")
		{
			init_flag |= FULL;
			stream.messages.erase(message);
			break;
		}
	}
}

std::string Connexion::get_foe_name()
{
	return (foe_name);
}

bool Connexion::is_start()
{
	stream.read_message();
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "start")
		{
			return (true);
		}
	}
	return (false);
}

void Connexion::send_message(Message message)
{
	stream.send_message(message);
}

void Connexion::cleanup()
{
	stream.cleanup();
}

void Connexion::sync_ball_racket_score(Ball ball, Racket racket1, Racket racket2)
{
	Message ball_loc("direction", std::to_string(ball.get_direction()));
	stream.send_message(ball_loc);
	Message ball_x("ballx", std::to_string(ball.get_x()));
	stream.send_message(ball_x);
	Message ball_y("bally", std::to_string(ball.get_y()));
	stream.send_message(ball_y);
	Message score1("score1", std::to_string(racket1.get_score()));
	stream.send_message(score1);
	Message score2("score2", std::to_string(racket2.get_score()));
	stream.send_message(score2);
	sync_racket(racket1);
}

void Connexion::sync_racket(Racket racket)
{
	Message racket_y("rackety", std::to_string(racket.get_y()));
	stream.send_message(racket_y);
}

int Connexion::get_racket_location()
{
	return (racket);
}

t_coord Connexion::get_ball_location()
{
	return (ball);
}

int Connexion::get_ball_direction()
{
	return (ball_direction);
}

void Connexion::update()
{
	stream.read_message();
	update_ball();
	update_racket();
	update_pause();
	update_is_over();
	update_score();
}

void Connexion::update_ball()
{
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "bally")
		{
			ball.y = atoi(message->get_content().c_str());
		}
		if (message->get_command() == "ballx")
		{
			ball.x = atoi(message->get_content().c_str());
		}
	}
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "direction")
		{
			ball_direction = atoi(message->get_content().c_str());
		}
	}
}

void Connexion::update_racket()
{
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "rackety")
		{
			racket = (atoi(message->get_content().c_str()));
		}
	}
}

void Connexion::update_pause()
{
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "pause")
			pause = true;
		if (message->get_command() == "unpause")
			pause = false;
	}
}

void Connexion::update_is_over()
{
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "EOG")
		{
			if (message->get_content() == "player")
				foe_left = true;
			else if (message->get_content() == "server")
					server_terminated = true;
			finished = true;
		}
	}
}

void Connexion::update_score()
{
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++ message)
	{
		if (message->get_command() == "score1")
		{
			score1 = atoi(message->get_content().c_str());
		}
		if (message->get_command() == "score2")
		{
			score2 = atoi(message->get_content().c_str());
		}
	}
}

void Connexion::send_end_of_game()
{
	Message message("EOG", "player");
	stream.send_message(message);
}

bool Connexion::is_pause()
{
	return (pause);
}

bool Connexion::is_game_over()
{
	return (finished);
}

void Connexion::send_pause_status(bool pause_status)
{
	if (pause_status == true)
	{
		Message message("pause", "");
		stream.send_message(message);
	}
	else
	{
		Message message("unpause", "");
		stream.send_message(message);
	}
}

int Connexion::get_score1()
{
	return (score1);
}

int Connexion::get_score2()
{
	return (score2);
}

bool Connexion::has_player_left()
{
	return (foe_left);
}

bool Connexion::has_server_stopped()
{
	return (server_terminated);
}
