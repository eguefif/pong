#include "def.h"

void to_non_blocking(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | SOCK_NONBLOCK);
}

SDL_Surface *load_surface(std::string path, SDL_Surface *sScreenSurface)
{
	SDL_Surface *optimized = NULL;

	SDL_Surface *loadedsurface = IMG_Load(path.c_str());
	if (loadedsurface == NULL)
	{
		std::cerr << "Impossible to load image" << std::endl;
		exit(EXIT_FAILURE);
	}
	optimized = SDL_ConvertSurface(loadedsurface, sScreenSurface->format, 0);
	if (optimized == NULL)
	{
		std::cerr << "Impossible to load image" << std::endl;
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(loadedsurface);
	return (optimized);
}
