#pragma once
#include "def.h"
#include "ball.h"
#include "racket.h"

class Renderer
{
	public:
		Renderer();
		enum side {LEFT = 0, RIGHT = 1};
		Renderer(SDL_Window *window);
		void render_scene(Ball ball, Racket racket1, Racket racket2) const;
		void render_winner(std::string name) const;
		void cleanup();
	
	private:
		SDL_Renderer *renderer = NULL;
		SDL_Window *window = NULL;
		TTF_Font *font = NULL;
		SDL_Color color = {255, 255, 255};
		Ball ball;
		std::vector<SDL_Surface*> scores;
		std::vector<std::string> images_path;

		void draw_ball(Ball ball) const;
		void draw_circle(t_coord location, float radius) const;
		void draw_racket(Racket racket) const;
		void draw_interface(Racket racket1, Racket racket2) const;
		void draw_names(Racket racket1, Racket racket2) const;
		void draw_line() const;
		void draw_scores(Racket racket1, Racket racket2) const;
		void draw_right_score(int score) const;
		void draw_left_score(int score) const;
		void draw_right_name(std::string name) const;
		void draw_left_name(std::string name) const;
		void init_img();
		void init_font();
};
