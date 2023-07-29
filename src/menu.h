#ifndef MENU_H
# define MENU_H
#define TITLE_DISTANCE 200
#include "def.h"

class Menu
{
	public:
		enum gameType {EXIT=0, LOCAL=1, REMOTE=2, COMPUTER=3};
		Menu(SDL_Window *aWindow);
		int run();

	private:
		void init();
		void load_image_path();
		void check_event();
		void move_selector_up();
		void move_selector_down();
		void render();
		void display_title();
		void display_selector();
		void display_menu_items();
		void cleanup();

		SDL_Window *window = NULL;
		bool stop = false;
		SDL_Surface *sScreenSurface = NULL;
		SDL_Surface *title = NULL;
		SDL_Surface *selector = NULL;
		std::string selector_path;
		std::string title_path;
		std::vector<std::string> images_path;
		std::vector<SDL_Surface*> images_surface;
		SDL_Event event;
		int selector_position = 1;
};

#endif
