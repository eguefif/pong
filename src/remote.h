#pragma once
#include "def.h"
#include "game.h"
#include "tcpstream.h"
#include "message.h"
#include "connexion.h"

class Remote : private Game
{
public:
	Remote(SDL_Window *window);
	virtual int run() override;

protected:
	virtual void check_event() override;
	virtual void cleanup() override;

private:
	void check_sdl_events();
	void check_keys();
	void init_remote_game();
	void set_player_name();
	void check_event_setname();
	bool init_connexion();
	void setup_game();
	void render_waiting_room();
	void check_event_waiting_room();
	void setup_if_ready();
	void check_start();
	void update_connexion();
	void check_connexion_pause();
	void check_connexion_game_over();
	void sync_as_player1();
	void sync_as_player2();
	void handle_disconnection();
	void render_end_of_game();
	void check_event_endgame();
	void switch_pause_remote();

	std::string name = "";
	Connexion conn;
	bool start = false;
	bool setup = false;
	bool back_to_menu = false;
	bool server_down = false;
	enum game_flag {
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
};
