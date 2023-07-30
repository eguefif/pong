#include "ia.h"

int IA::where_to_go(Ball ball, Racket racket)
{
	int retval = 0;

	srand(time(NULL));
	retval = rand() % 3;
	if (ball.get_x() < SCREEN_WIDTH / 2 - 200)
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
	return (retval);
}
