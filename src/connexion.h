#pragma once
#include "def.h"
#include "tcpstream.h"
#include "message.h"

class Connexion
{
public:
	Connexion() = default;
	Connexion(std::string add, int aport);
	enum e_init_flag {
			NAME = 1 << 0,
			BALL = 1 << 1,
			READY = 1 << 2,
			WAITING = 1 << 3,
			JOINING = 1 << 4,
			PLAYER1 = 1 << 5,
			FULL = 1 << 6
		};
	bool connect_to_server();
	bool is_setup_done();
	int get_ball_direction();
	bool is_player1();
	std::string get_foe_name();
	bool waiting_to_start();
	void send_message(Message message);

private:
	std::string address = "127.0.0.1";
	int port = 5000;
	TCP_Stream stream;
	int init_flag = 0;
	int ball_direction = 0;
	std::string foe_name;

	void check_message();
};
