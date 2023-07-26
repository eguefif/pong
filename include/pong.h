#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "menu.h"
#include "remote.h"
#include "computer.h"
#include "local.h"
#include "objects.h"
#include "renderer.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int RACKET_SIZE = SCREEN_HEIGHT / 20;
const int RACKET_WIDTH = 10;
const int BALL_SIZE = 6;


class Pong
{
	public:
		enum gameType {LOCAL=0, REMOTE=1, COMPUTER=2, EXIT=3};
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
