#ifndef MENU_H
# define MENU_H
#include <SDL_ttf.h>

class Menu
{
	public:
		enum gameType {EXIT=0, COMPUTER=1, LOCAL=2, REMOTE=3};
		SDL_Surface *gScreenSurface = NULL;
		SDL_Surface *gNewGame = NULL;
		SDL_Surface *gExit = NULL;
		SDL_Window *window = NULL;
		SDL_Event event;
		bool quit = false;
		int gameType = EXIT;

		Menu(SDL_Window *aWindow);
		int onRun();

	private:
		void onInit();
		void onEvent();
		void onUpdate();
		void onRender();
		void onCleanup();
};

#endif
