#pragma once
#include "def.h"
#include "game.h"

class Local : protected Game
{
	public:
		Local(SDL_Window *window);
		using Game::run;

	protected:
		virtual void check_event() override;

	private:
		void check_keys();
		void check_sdl_events();
};
