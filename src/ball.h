#pragma once
#include "def.h"
#include "racket.h"

class Ball
{
	public:
		Ball();
		enum side {LEFT = 0, RIGHT = 1};
		void move(Racket racket1, Racket racket2);
		bool is_scorer();
		float get_radius();
		int get_scorer();
		t_coord get_location();
		int get_direction();
		int get_x();
		int get_y();
		int get_vy();
		int get_vx();
		void set_location(t_coord loc);
		void set_direction(int n);
		void rand_direction();

	private:
		t_coord location;
		int		x_vec;
		int		y_vec;
		float	radius = 15.0;
		int		scorer = -1;

		void check_collision(Racket racket1, Racket racket2);
		void reverse_y_vec();
		void reverse_x_vec();
};
