#pragma once
#include "def.h"
#include "game.h"
#include "tcpstream.h"
#include "message.h"

class Remote : private Game
{
	public:
		Remote(SDL_Window *window);
		enum e_init_flag {
			NAME = 1 << 0,
			BALL = 1 << 1,
			READY = 1 << 2
		};
		virtual int onRun() override;
	
	protected:
		virtual void onEvent() override;
	
	private:
		void check_events();
		void check_keys();
		void init_remote_game();
		void set_name();
		void init_connexion();
		void setup_game();
		bool is_init_done();
		void render_waiting_room();

		std::string name = "";
		TCP_Stream stream;
		int init_flag = 0;
};
