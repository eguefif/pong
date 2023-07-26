#pragma once
#include "def.h"
#include "game.h"

class Remote : private Game
{
	public:
		Remote(SDL_Window *window);
		using Game::onRun;
	
	protected:
		virtual void onEvent() override;
};
