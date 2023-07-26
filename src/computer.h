#pragma once
#include "pong.h"
#include "game.h"

class Computer : private Game
{
	public:
		Computer(SDL_Window *window);
		using Game::onRun;
	
	protected:
		virtual void onEvent() override;
		void onUpdate();
		void onRender() const;

		SDL_Window *window = NULL;
		bool quit = false;
		SDL_Event event;
};
