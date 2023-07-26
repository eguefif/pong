#ifndef MENU_H
# define MENU_H
#define TITLE_DISTANCE 200
#include "def.h"

class Menu
{
	public:
		enum gameType {EXIT=0, COMPUTER=1, LOCAL=2, REMOTE=3};
		Menu(SDL_Window *aWindow);
		int onRun();

	private:
		void onInit();
		void onEvent();
		void onUpdate();
		void onRender();
		void onCleanup();
		void load_image_path();
		void display_title();
		void display_selector();
		void move_selector_up();
		void move_selector_down();

		SDL_Color color = {0, 0, 0};
		SDL_Surface *sScreenSurface = NULL;
		SDL_Surface *title = NULL;
		std::string title_path;
		SDL_Surface *selector = NULL;
		std::string selector_path;
		SDL_Window *window = NULL;
		SDL_Event event;
		SDL_Renderer *renderer;
		bool quit = false;
		std::vector<std::string> images_path;
		std::vector<SDL_Surface*> images_surface;
		int selector_position = 0;
};

#endif
