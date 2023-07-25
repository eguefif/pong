#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "menu.h"
#ifndef PONG_H
# define PONG_H

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RACKET_SIZE = SCREEN_HEIGHT / 20;
const int RACKET_WIDTH = 10;
const int BALL_SIZE = 6;

typedef struct s_coord
{
	int x;
	int y;
}		coord;

class Object
{
	public:
		Object(coord aLocation);
		virtual void display(SDL_Surface *aSurface);
		void updateCoord(coord newLocation);
		coord location;
};

class Racket : public Object
{
	Racket(int side);
	virtual void display(SDL_Surface *aSurface);
};

class Ball : public Object
{
	Ball(coord location);
	virtual void display(SDL_Surface *aSurface);
};

class Game
{
	public:
		Game(SDL_Window *aWindow);
		void onRun();
		void onEvent();
		void onUpdate();
		void onRender() const;
	
		SDL_Window *window = NULL;
		bool quit = false;
		SDL_Event event;
};

class Pong
{
	public:
		enum gameType {EXIT=0, COMPUTER=1, LOCAL=2, REMOTE=3};
		enum side {LEFT=0, RIGHT=1};
		void onRun();

	private:
		SDL_Window *window = NULL;
		SDL_Surface *screenSurface = NULL;
		SDL_Event event;
		bool quit = false;

		void onInit();
		int onMenu();
		void onCreateGame(int type);
		void onCleanup();
		void onEvent();
};

#endif
