#include "menu.h"

Menu::Menu(SDL_Window *aWindow) :
	window(aWindow)
{}

int Menu::run()
{
	init();
	while(!stop)
	{
		check_event();
		render();
	}
	cleanup();
	if (selector_position == 4)
		selector_position = EXIT;
	return (selector_position);
}

void Menu::init()
{
	int img_flag = IMG_INIT_PNG;
	load_image_path();
	if (!(IMG_Init(img_flag) & img_flag))
	{
		std::cerr << "Error while initializing img for png" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		sScreenSurface = SDL_GetWindowSurface(window);
		title = load_surface(title_path, sScreenSurface);
		selector = load_surface(selector_path, sScreenSurface);
		for (auto path : images_path)
			images_surface.push_back(load_surface(path, sScreenSurface));
	}
}

void Menu::load_image_path()
{
	std::string pvpr = "./ressource/pvpr.png";
	std::string pvpl = "./ressource/pvpl.png";
	std::string pvc = "./ressource/pvc.png";
	std::string exit = "./ressource/exit.png";

	title_path = "./ressource/pong.png";
	selector_path = "./ressource/selector.png";
	images_path.push_back(pvpl);
	images_path.push_back(pvpr);
	images_path.push_back(pvc);
	images_path.push_back(exit);
}

void Menu::check_event()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			stop = true;
			selector_position = EXIT;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_UP: move_selector_up();
							  break;
				case SDLK_DOWN: move_selector_down();
								break;
				case SDLK_SPACE:
				case SDLK_RETURN: stop = true;
								  break;
				case SDLK_ESCAPE: stop = true;
								  selector_position = EXIT;
								  break;
				default: break;
			}
		}
	}
}

void Menu::move_selector_up()
{
	if (selector_position == 1)
		selector_position = 4;
	else
		selector_position -= 1;
}

void Menu::move_selector_down()
{
	if (selector_position == 4)
		selector_position = 1;
	else
		selector_position += 1;
}

void Menu::render()
{
	SDL_FillRect(sScreenSurface, NULL, 0x000000);
	display_title();
	display_selector();
	display_menu_items();
	SDL_UpdateWindowSurface(window);
}

void Menu::display_menu_items()
{
	int y;
	SDL_Rect dst;

	y = TITLE_DISTANCE;
	for (auto surface : images_surface)
	{
		dst.w = surface->w;
		dst.h = surface->h;
		dst.x = SCREEN_WIDTH / 2 - surface->w / 2;
		dst.y = y;
		SDL_BlitSurface(surface, NULL, sScreenSurface, &dst);
		y += dst.h + 10;
	}
}

void Menu::display_title()
{
	SDL_Rect dst;

	dst.w = title->w;
	dst.h = title->h;
	dst.x = SCREEN_WIDTH / 2 - title->w / 2;
	dst.y = 5;
	SDL_BlitSurface(title, NULL, sScreenSurface, &dst);
}

void Menu::display_selector()
{
	SDL_Rect dst;

	dst.w = selector->w;
	dst.h = selector->h;
	dst.x = SCREEN_WIDTH / 2 - images_surface[selector_position-1]->w / 2 - selector->w - 10;
	dst.y = TITLE_DISTANCE + images_surface[1]->h * (selector_position-1) + 10 ;
	SDL_BlitScaled(selector, NULL, sScreenSurface, &dst);
}

void Menu::cleanup()
{
	for (auto image_surface = images_surface.begin();
			image_surface != images_surface.end();
			++image_surface)
	{
		SDL_FreeSurface(*image_surface);
		*image_surface = NULL;
	}
	images_path.clear();
	SDL_FreeSurface(sScreenSurface);
	sScreenSurface = NULL;
}
