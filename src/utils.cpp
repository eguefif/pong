#include "def.h"

SDL_Surface *load_surface(std::string path, SDL_Surface *sScreenSurface)
{
	SDL_Surface *optimized_surface = NULL;

	SDL_Surface *loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL)
	{
		std::cerr << "Impossible to load img: " << path.c_str() << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		optimized_surface = SDL_ConvertSurface(loaded_surface, sScreenSurface->format, 0);
		if (optimized_surface == NULL)
		{
			std::cerr << "Error while converting image: " << path.c_str() << std::endl;
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(loaded_surface);
	}
	return (optimized_surface);
}
