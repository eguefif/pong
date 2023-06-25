#include <SDL2/SDL.h>
#include <iostream>
#ifndef APP_H
# define APP_H

class Pong
{
	public:
		Pong();
		void onRun();

	private:
		SDL_Window *window = NULL;
		SDL_Surface *screenSurface = NULL;
		SDL_Event event;
		bool quit = false;
		Game game;
		enum gameType {EXIT=0, COMPUTER=1, LOCAL=2, REMOTE=3};
		void onInit();
		int onMenu();
		void onCreateGame(int type);
		void onCleanup();
		void onEvent();
};

class Game
{
	public:
		void onRun();
	
	private:
	SDL_Window window;
}
#endif
