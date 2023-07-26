#pragma once
#include "def.h"
#include "game.h"

class Computer : private Game
{
	public:
		Computer(SDL_Window *window);
		using Game::onRun;
	
	protected:
		virtual void onEvent() override;
};
