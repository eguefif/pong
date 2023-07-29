#include "ia.h"

int IA::where_to_go(Ball ball, Racket racket)
{
	int retval = 0;

	srand(time(NULL));
	retval = rand() % 3;
	if (ball.get_x() < SCREEN_WIDTH / 2)
	{
		if (ball.get_y() < (racket.get_y() + RACKET_HEIGHT / 2))
		{
			retval = UP;
		}
		else
		{
			retval = DOWN;
		}
	}

	std::cout << "ball x: " << ball.get_x() << std::endl;
	std::cout << "ball y: " << ball.get_y() << " racket y: " << racket.get_y() + RACKET_HEIGHT/2 << std::endl;
	std::cout << "direction: " << retval << std::endl;
	return (retval);
}
