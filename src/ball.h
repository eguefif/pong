#pragma once
#include "def.h"
#include "racket.h"

class Ball
{
	public:
		Ball();
		enum side {LEFT = 0, RIGHT = 1};
		void move(Racket racket1, Racket racket2);
		float get_radius();
		t_coord get_location();
		bool is_score(Racket racket1, Racket racket2);
		int get_scorer();
		void set_location(t_coord loc);

	private:
		t_coord location;
		int		x_vec;
		int		y_vec;
		float	radius = 15.0;
		int		scorer = -1;

		void check_collision(Racket racket1, Racket racket2);
		void reverse_y_vec();
		void reverse_x_vec();
		void score_right(Racket racket1, Racket racket2);
		void score_left(Racket racket1, Racket racket2);
};