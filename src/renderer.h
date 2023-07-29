#pragma once
#include "def.h"
#include "ball.h"
#include "racket.h"
#include "connexion.h"

class Renderer
{
public:
	Renderer();
	enum side {LEFT = 0, RIGHT = 1};
	Renderer(SDL_Window *window);
	void render_scene(Ball ball, Racket racket1, Racket racket2) const;
	void render_winner(std::string name) const;
	void cleanup();
	void render_text(std::string str, t_coord location);
	void clear_screen();
	void render_end_game(Connexion conn, bool server_down);
	void render_waiting_room(Connexion conn, Racket racket1, Racket racket2, std::string name);
	void render_now();

private:
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	TTF_Font *font = NULL;
	SDL_Color color = {255, 255, 255};
	Ball ball;
	std::vector<SDL_Surface*> scores;

	void init_renderer();
	void init_img();
	void init_font();
	void draw_interface(Racket racket1, Racket racket2) const;
	void draw_scores(Racket racket1, Racket racket2) const;
	void draw_left_score(int score) const;
	void draw_right_score(int score) const;
	void draw_names(Racket racket1, Racket racket2) const;
	void draw_right_name(std::string name) const;
	void draw_left_name(std::string name) const;
	void draw_line() const;
	void draw_ball(Ball ball) const;
	void draw_circle(t_coord location, float radius) const;
	void draw_racket(Racket racket) const;
	enum game_flag {
			NAME = 1 << 0,
			BALL = 1 << 1,
			READY = 1 << 2,
			WAITING = 1 << 3,
			JOINING = 1 << 4,
			PLAYER1 = 1 << 5,
			FULL = 1 << 6,
			START = 1 << 7,
			PAUSE = 1 << 8,
			GAMEOVER = 1 << 9,
			FOELEFT = 1 << 10,
			SERVER_TERM = 1 << 11,
			FINISHED = 1 << 12,
			SERVER_DISCONNECT = 1 << 13,
			PLAYER_LEFT = 1 << 14
		};
};
