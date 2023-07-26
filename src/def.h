#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int TOP_EDGE = 50;
const int RACKET_HEIGHT = SCREEN_HEIGHT / 10;
const int RACKET_WIDTH = 15;
const int RACKET_SPEED = 3;
const float RADIUS = 25;
const int BALL_SPEED = 3;
const float PI = 3.141592;

typedef struct s_coord
{
	int x;
	int y;
}		t_coord;

SDL_Surface *load_surface(std::string path, SDL_Surface *sScreenSurface);