#pragma once
#include "pong.h"
#include "objects.h"
#include "renderer.h"

class Game
{
	public:
		Game(SDL_Window *awindow);
		void onRun();

		virtual void onEvent() = 0;
		void onUpdate();
		void onRender() const;

		SDL_Window *window = NULL;
		bool quit = false;
		SDL_Event event;
		Renderer renderer;
		Ball ball;
};
