#pragma once
#include "def.h"
#include "menu.h"
#include "remote.h"
#include "computer.h"
#include "local.h"
#include "game.h"

class Pong
{
	public:
		enum gameType {EXIT=0, LOCAL=1, REMOTE=2, COMPUTER=3};
		enum side {LEFT=0, RIGHT=1};
		void run();

	private:
		SDL_Window *window = NULL;
		bool quit = false;
		int game_type = COMPUTER;

		void init_sdl_and_window();
		void run_menu();
		void run_game();
		void cleanup();
};
