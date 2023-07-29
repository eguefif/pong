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

bool Connexion::check_flags(int flag)
{
	update();
	return (game_flags & flag);
}

void Connexion::set_flags(int flag)
{
	game_flags |= flag;
}

void Connexion::unset_flags(int flag)
{
	game_flags &= ~flag;
}

void Connexion::flip_flags(int flag)
{
	game_flags ^= flag;
}

bool Connexion::is_setup_ready()
{
	update();
	return (((game_flags & NAME) == NAME) && ((game_flags & BALL) == BALL) && ((game_flags & FULL) == FULL));
}

std::string Connexion::get_foe_name()
{
	return (foe_name);
}

void Connexion::send_message(Message message)
{
	stream.send_message(message);
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
	for (auto message = stream.messages.begin(); message != stream.messages.end(); ++message)
	{
		if (message->get_command() == "bally")
			ball.y = atoi(message->get_content().c_str());
		if (message->get_command() == "ballx")
			ball.x = atoi(message->get_content().c_str());
		if (message->get_command() == "direction")
			ball_direction = atoi(message->get_content().c_str());
		if (message->get_command() == "rackety")
			racket = (atoi(message->get_content().c_str()));
		if (message->get_command() == "pause")
		{
			set_flags(PAUSE);
		}
		if (message->get_command() == "unpause")
		{
			unset_flags(PAUSE);
		}
		if (message->get_command() == "EOG")
		{
			if (message->get_content() == "player")
				set_flags(PLAYER_LEFT);
			else if (message->get_content() == "server")
				set_flags(SERVER_TERM);
			set_flags(FINISHED);
		}
		if (message->get_command() == "score1")
			score1 = atoi(message->get_content().c_str());
		if (message->get_command() == "score2")
			score2 = atoi(message->get_content().c_str());
		if (message->get_command() == "start")
			set_flags(START);
		if (message->get_command() == "waiting")
		{
			set_flags(WAITING);
			set_flags(PLAYER1);
		}
		if (message->get_command() == "joining")
			set_flags(JOINING);
		if (message->get_command() == "ball")
		{
			set_flags(BALL);
			ball_direction = atoi(message->get_content().c_str());
		}
		if (message->get_command() == "name")
		{
			set_flags(NAME);
			foe_name = message->get_content();
		}
		if (message->get_command() == "ready")
			set_flags(READY);
		if (message->get_command() == "full")
			set_flags(FULL);
	}
	stream.messages.clear();
}

void Connexion::send_end_of_game()
{
	Message message("EOG", "player");
	stream.send_message(message);
}

void Connexion::send_pause_status(bool pause)
{
	if (pause)
	{
		Message message("pause", "");
		send_message(message);
	}
	else
	{
		Message message("unpause", "");
		send_message(message);
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

void Connexion::cleanup()
{
	stream.cleanup();
}

