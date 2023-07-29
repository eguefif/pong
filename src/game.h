#pragma once
#include "def.h"
#include "ball.h"
#include "racket.h"
#include "renderer.h"

class Game
{
	public:
		Game(SDL_Window *awindow);
		virtual int onRun();

		virtual void onEvent() = 0;
		void onUpdate();
		void onRender() const;
		virtual void onCleanup();
		void switch_pause();
		void reset();
		void set_winner_name();

		SDL_Window *window = NULL;
		bool quit = false;
		bool stop = false;
		bool pause = true;
		bool winner = false;
		SDL_Event event;
		Renderer renderer;
		Ball ball;
		Racket racket1;
		Racket racket2;
		std::string winner_name;
};
