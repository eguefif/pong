#include "ball.h"

Ball::Ball()
{
	location.x = SCREEN_WIDTH / 2;
	location.y = SCREEN_HEIGHT / 2;
	radius = RADIUS;
	srand(time(NULL));
	if (rand() % 2)
		x_vec = BALL_SPEED;
	else
		x_vec = -BALL_SPEED;
	if (rand() % 2)
		y_vec = BALL_SPEED;
	else
		y_vec = -BALL_SPEED;
}

float Ball::get_radius()
{
	return (radius);
}

t_coord Ball::get_location()
{
	return (location);
}

void Ball::move(Racket racket1, Racket racket2)
{
	check_collision(racket1, racket2);
	location.x += x_vec;
	location.y += y_vec;
}

void Ball::check_collision(Racket racket1, Racket racket2)
{
	if (location.y + radius >= SCREEN_HEIGHT)
		reverse_y_vec();
	else if (location.y - radius <= TOP_EDGE)
		reverse_y_vec();
	if (racket1.is_colliding(location))
		reverse_x_vec();
	else if (racket2.is_colliding(location))
		reverse_x_vec();
}

void Ball::reverse_x_vec()
{
	x_vec = -x_vec;
}

void Ball::reverse_y_vec()
{
	y_vec = -y_vec;
}

bool Ball::is_score()
{
	scorer = -1;
	if (location.x + radius > SCREEN_WIDTH)
	{
		scorer = RIGHT;
		return (true);
	}
	else if (location.x - radius < 0)
	{
		scorer = LEFT;
		return (true);
	}
	return (false);
}

void Ball::score_right(Racket racket1, Racket racket2)
{
	if (racket1.get_side() == RIGHT)
		racket1.update_score();
	else
		racket2.update_score();
}

void Ball::set_location(t_coord loc)
{
	srand(time(NULL));
	if (rand() % 2)
		x_vec = BALL_SPEED;
	else
		x_vec = -BALL_SPEED;
	if (rand() % 2)
		y_vec = BALL_SPEED;
	else
		y_vec = -BALL_SPEED;
	location = loc;
}

int Ball::get_scorer()
{
	return (scorer);
}

void Ball::set_direction(int n)
{
	switch (n)
	{
		case (0): x_vec = BALL_SPEED;
				  y_vec = BALL_SPEED;
				  break;
		case (1): x_vec = -BALL_SPEED;
				  y_vec = BALL_SPEED;
				  break;
		case (2): x_vec = BALL_SPEED;
				  y_vec = -BALL_SPEED;
				  break;
		case (3): x_vec = -BALL_SPEED;
				  y_vec = -BALL_SPEED;
				  break;
	}
}
