#include "racket.h"

Racket::Racket(int aside):
	side(aside)
{
	location.y = SCREEN_HEIGHT / 2 - RACKET_HEIGHT / 2;
	if (side == LEFT)
	{
		location.x = 0;
		name = "player 1";
	}
	else
	{
		location.x = SCREEN_WIDTH - RACKET_WIDTH;
		name = "player 2";
	}
}

void Racket::up()
{
	y_vec -= RACKET_SPEED;
}

void Racket::down()
{
	y_vec += RACKET_SPEED;
}

void Racket::move()
{
	if (!is_collision())
		location.y += y_vec;
	y_vec = 0;
}

bool Racket::is_colliding(t_coord loc)
{
	if (side == LEFT)
	{
		if (loc.x - RADIUS <= location.x + RACKET_WIDTH && is_at_racket_level(loc.y))
			return (true);
	}
	else if (side == RIGHT)
	{
		if (loc.x + RADIUS >= location.x && is_at_racket_level(loc.y))
			return (true);
	}
	return (false);
}

bool Racket::is_collision()
{
	if (y_vec > 0)
	{
		if (location.y + RACKET_HEIGHT >= SCREEN_HEIGHT)
			return true;
	}
	else if (y_vec < 0)
	{
		if (location.y <= TOP_EDGE + 1)
			return true;
	}
	return false;
}

int Racket::get_x()
{
	return (location.x);
}

int Racket::get_y()
{
	return (location.y);
}


bool Racket::is_at_racket_level(int y)
{
	if (y > location.y && y < location.y + RACKET_HEIGHT)
		return (true);
	return (false);
}

int Racket::get_side()
{
	return (side);
}

void Racket::update_score()
{
	score += 1;
}

int Racket::get_score() const
{
	return (score);
}

std::string Racket::get_name()
{
	return (name);
}

void Racket::set_name(std::string aname)
{
	name = aname;
}

void Racket::set_location(int new_y)
{
	location.y = new_y;
}

void Racket::set_score(int sc)
{
	score = sc;
}
