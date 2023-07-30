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

void Ball::move(Racket racket1, Racket racket2)
{
	check_collision(racket1, racket2);
	location.x += x_vec;
	location.y += y_vec;
}

bool Ball::is_scorer()
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

float Ball::get_radius()
{
	return (radius);
}

t_coord Ball::get_location()
{
	return (location);
}

void Ball::check_collision(Racket racket1, Racket racket2)
{
	if (location.y + radius >= SCREEN_HEIGHT)
		reverse_y_vec();
	else if (location.y - radius <= TOP_EDGE)
		reverse_y_vec();
	if (racket1.is_colliding(location))
	{
		reverse_x_vec();
		set_location({0 + RACKET_WIDTH + (int) RADIUS / 2 + 15, location.y});
	}
	else if (racket2.is_colliding(location))
	{
		reverse_x_vec();
		set_location({racket2.get_x() + (int) RADIUS / 2 - 15, location.y});
	}
}

void Ball::reverse_x_vec()
{
	x_vec = -x_vec;
}

void Ball::reverse_y_vec()
{
	y_vec = -y_vec;
}

void Ball::set_location(t_coord loc)
{
	location = loc;
}

void Ball::rand_direction()
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

int Ball::get_direction()
{
	int dir;

	if ((x_vec == BALL_SPEED) && (y_vec == BALL_SPEED))
		dir = 0;
	else if ((x_vec == -BALL_SPEED) && (y_vec == BALL_SPEED))
		dir= 1;
	else if ((x_vec == BALL_SPEED) && (y_vec == -BALL_SPEED))
		dir = 2;
	else if ((x_vec == -BALL_SPEED) && (y_vec == -BALL_SPEED))
		dir= 3;
	return (dir);
}

int Ball::get_x()
{
	return (location.x);
}

int Ball::get_y()
{
	return (location.y);
}

int Ball::get_vy()
{
	return (y_vec);
}

int Ball::get_vx()
{
	return (x_vec);
}
