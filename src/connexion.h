#pragma once
#include "def.h"
#include "tcpstream.h"
#include "message.h"
#include "ball.h"
#include "racket.h"
enum e_game_flag {
		NAME = 1 << 0,
		BALL = 1 << 1,
		READY = 1 << 2,
		WAITING = 1 << 3,
		JOINING = 1 << 4,
		PLAYER1 = 1 << 5,
		FULL = 1 << 6,
		START = 1 << 7,
		PAUSE = 1 << 8,
		GAMEOVER = 1 << 9,
		FOELEFT = 1 << 10,
		SERVER_TERM = 1 << 11,
		FINISHED = 1 << 12,
		SERVER_DISCONNECT = 1 << 13,
		PLAYER_LEFT = 1 << 14
	};

class Connexion
{
public:
	Connexion() = default;
	Connexion(std::string add, int aport);
	bool check_flags(int flag);
	void set_flags(int flag);
	void unset_flags(int flag);
	void flip_flags(int flag);
	bool connect_to_server();
	bool is_setup_ready();
	void send_message(Message message);
	void sync_ball_racket_score(Ball ball, Racket racket1, Racket racket2);
	void sync_racket(Racket racket);
	void send_end_of_game();
	void send_pause_status(bool pause);
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
	int game_flags = 0;
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

	void update_ball();
	void update_racket();
	void update_pause();
	void update_is_over();
	void update_score();
};
