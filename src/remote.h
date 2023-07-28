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
		void render_waiting_room();
		void check_event_waiting_room();
		void setup_if_ready();

		std::string name = "";
		Connexion conn;
};
