#pragma once
#include "def.h"
#include "game.h"
#include "ia.h"

class Computer : private Game
{
	public:
		Computer(SDL_Window *window);
		using Game::onRun;
	
	protected:
		virtual void onEvent() override;
		void check_events();
		void check_keys();
		void check_ia();
		
		IA ia;
};
