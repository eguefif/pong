#include "menu.h"

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
	return selector_position;
}

void Menu::onInit()
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
	std::string image3 = "./ressource/pvpr.png";
	std::string image2 = "./ressource/pvpl.png";
	std::string image4 = "./ressource/pvc.png";
	std::string image5 = "./ressource/exit.png";
	std::string image1 = "./ressource/pong.png";
	std::string selector = "./ressource/selector.png";

	title_path = image1;
	selector_path = selector;
	images_path.push_back(image2);
	images_path.push_back(image3);
	images_path.push_back(image4);
	images_path.push_back(image5);
}

void Menu::onEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			quit = true;
			selector_position = 3;
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
				case SDLK_RETURN: quit = true;
								  break;
				case SDLK_ESCAPE: quit = true;
								  selector_position = 3;
								  break;
				default: break;
			}
		}
	}
}

void Menu::onUpdate()
{}

void Menu::onRender()
{
	int y;
	SDL_Rect dst;

	SDL_FillRect(sScreenSurface, NULL, 0x000000);
	display_title();
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
	display_selector();
	SDL_UpdateWindowSurface(window);
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
	dst.x = SCREEN_WIDTH / 2 - images_surface[selector_position]->w / 2 - selector->w - 10;
	dst.y = TITLE_DISTANCE + images_surface[1]->h * selector_position + 10 ;
	SDL_BlitScaled(selector, NULL, sScreenSurface, &dst);
}

void Menu::move_selector_up()
{
	if (selector_position == 0)
		selector_position = 3;
	else
		selector_position -= 1;
}

void Menu::move_selector_down()
{
	if (selector_position == 3)
		selector_position = 0;
	else
		selector_position += 1;
}

void Menu::onCleanup()
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
