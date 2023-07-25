#include "pong.h"

Menu::Menu(SDL_Window *aWindow) :
	window(aWindow)
{}

int Menu::onRun()
{
	onInit();
	while(!quit)
	{
		onEvent();
		onUpdate();
		onRender();
	}
	onCleanup();
	return gameType;
}

void Menu::onInit()
{
	int imgFlags = IMG_INIT_PNG;
	SDL_Surface *tempSurface = NULL;

	if (!(IMG_Init(imgFlags) & imgFlags))
		std::cerr << "SDL_image could not initialize! SDL_image error: %s\n", IMG_GetError();
	else
	{
		gScreenSurface = SDL_GetWindowSurface(window);
		tempSurface = SDL_LoadBMP("newgame.bmp");
		gNewGame = SDL_ConvertSurface(tempSurface, gScreenSurface->format, 0);
		tempSurface = SDL_LoadBMP("exit.bmp");
		gExit = SDL_ConvertSurface(tempSurface, gScreenSurface->format, 0);
		SDL_FreeSurface(tempSurface);
		tempSurface = NULL;
	}
}

void Menu::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
		if (event.type == SDL_QUIT)
			quit = true;
}

void Menu::onUpdate()
{}

void Menu::onRender()
{
	SDL_Rect finalSurfaceNewgame;
	finalSurfaceNewgame.x = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 6;
	finalSurfaceNewgame.y = SCREEN_HEIGHT / 10;
	finalSurfaceNewgame.w = SCREEN_WIDTH / 3;
	finalSurfaceNewgame.h = SCREEN_HEIGHT / 3;
	SDL_BlitScaled(gNewGame, NULL, gScreenSurface, &finalSurfaceNewgame);
	finalSurfaceNewgame.y = SCREEN_HEIGHT / 10 + 100;
	SDL_BlitScaled(gExit, NULL, gScreenSurface, &finalSurfaceNewgame);
	SDL_UpdateWindowSurface(window);
}

void Menu::onCleanup()
{
	SDL_FreeSurface(gNewGame);
	gNewGame = NULL;
	SDL_FreeSurface(gExit);
	gExit = NULL;
}
