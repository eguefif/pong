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
		enum gameType {LOCAL=0, REMOTE=1, COMPUTER=2, EXIT=3};
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
