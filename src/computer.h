#pragma once
#include "def.h"
#include "game.h"
#include "ia.h"

class Computer : private Game
{
	public:
		Computer(SDL_Window *window);
		using Game::run;
	
	protected:
		virtual void check_event() override;
		void check_sdl_events();
		void check_keys();
		void check_ia();
		
		IA ia;
};
