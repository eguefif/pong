#pragma once
#include "pong.h"

class Game
{
	public:
		void onRun();

		virtual void onEvent() = 0;
		void onUpdate();
		void onRender() const;

		SDL_Window *window = NULL;
		bool quit = false;
		SDL_Event event;
		Ball ball;
};
