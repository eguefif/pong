#pragma once
#include "def.h"
#include "tcpstream.h"
#include "message.h"
#include "ball.h"
#include "racket.h"

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
	bool is_setup_ready();
	bool is_player1();
	bool is_pause();
	bool is_start();
	bool is_game_over();
	bool has_player_left();
	bool has_server_stopped();
	void send_message(Message message);
	void sync_ball_racket_score(Ball ball, Racket racket1, Racket racket2);
	void sync_racket(Racket racket);
	void send_end_of_game();
	void send_pause_status(bool pause_status);
	void update();
	int get_ball_direction();
	std::string get_foe_name();
	int get_score1();
	int get_score2();
	int get_racket_location();
	t_coord get_ball_location();
	void cleanup();

private:
	TCP_Stream stream;
	std::string address = "127.0.0.1";
	int port = 5000;
	int init_flag = 0;
	int ball_direction = 0;
	std::string foe_name;
	bool pause = false;
	bool finished = false;
	t_coord ball;
	int racket;
	int score1 = 0;
	int score2 = 0;
	bool server_terminated = false;
	bool foe_left = false;

	void check_message();
	void update_ball();
	void update_racket();
	void update_pause();
	void update_is_over();
	void update_score();
};
