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

		std::string name = "";
		Connexion conn;
		bool start = false;
		bool setup = false;
		bool back_to_menu = false;
		bool server_down = false;
};
