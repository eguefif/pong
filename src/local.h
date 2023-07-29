#pragma once
#include "def.h"
#include "game.h"

class Local : protected Game
{
	public:
		Local(SDL_Window *window);
		using Game::onRun;

	protected:
		virtual void onEvent() override;

	private:
		void check_keys();
		void check_events();
};
