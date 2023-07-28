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

bool Connexion::is_setup_done()
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
			std::cout << "Waiting" << std::endl;
			init_flag |= WAITING;
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "joining")
		{
			std::cout << "Joing" << std::endl;
			init_flag |= JOINING;
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "ball")
		{
			std::cout << "ball" << std::endl;
			init_flag |= BALL;
			ball_direction = atoi(message->get_content().c_str());
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "name")
		{
			std::cout << "Name" << std::endl;
			init_flag |= NAME;
			foe_name = message->get_content();
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "ready")
		{
			std::cout << "Ready" << std::endl;
			init_flag |= READY;
			stream.messages.erase(message);
			break;
		}
		if (message->get_command() == "full")
		{
			std::cout << "Full" << std::endl;
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

int Connexion::get_ball_direction()
{
	return (ball_direction);
}

bool Connexion::waiting_to_start()
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
