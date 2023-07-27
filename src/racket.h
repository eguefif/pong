#pragma once
#include "def.h"

class Racket
{
	public:
		enum sides {LEFT = 0, RIGHT = 1};
		Racket(int aside);
		bool is_colliding(t_coord loc);
		int get_side();
		std::string get_name();
		void set_name(std::string aname);
		int get_x();
		int get_y();
		void up();
		void down();
		void move();
		void update_score();
		int get_score() const;

	private:
		t_coord location;
		int		y_vec = 0;
		int		side;
		int		score = 0;
		std::string name;

		bool is_collision();
		bool is_at_racket_level(int y);
};
