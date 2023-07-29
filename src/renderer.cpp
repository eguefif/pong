#include "renderer.h"

extern const float PI;

Renderer::Renderer()
{}

Renderer::Renderer(SDL_Window *awindow) :
	window(awindow)
{
	init_renderer();
	init_img();
	init_font();
}

void Renderer::init_renderer()
{
	SDL_Renderer *aRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (aRenderer == NULL)
	{
		std::cout << "Impossible to create a sdl renderer." << std::endl;
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawColor(aRenderer, 0x00, 0x00, 0x00, 0x00);
	renderer = aRenderer;
}

void Renderer::init_font()
{
	if (TTF_Init() < 0)
	{
		std::cerr << "Impossible to init TTF_Init" << std::endl;
		exit(EXIT_FAILURE);
	}
	font = TTF_OpenFont("./ressource/font.ttf", 50);
	if (font == NULL)
	{
		std::cerr << "Impossible to load font" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Renderer::init_img()
{
	std::vector<std::string> images_path;

	std::string zero = "./ressource/0.png";
	std::string un = "./ressource/1.png";
	std::string deux = "./ressource/2.png";
	std::string trois = "./ressource/3.png";
	std::string quatre = "./ressource/4.png";
	std::string cinq = "./ressource/5.png";
	
	images_path.push_back(zero);
	images_path.push_back(un);
	images_path.push_back(deux);
	images_path.push_back(trois);
	images_path.push_back(quatre);
	images_path.push_back(cinq);

	for (auto path : images_path)	
		scores.push_back(load_surface(path, SDL_GetWindowSurface(window)));
}
	
void Renderer::render_scene(Ball ball, Racket racket1, Racket racket2) const
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	draw_interface(racket1, racket2);
	draw_ball(ball);
	draw_racket(racket1);
	draw_racket(racket2);
	SDL_RenderPresent(renderer);
}

void Renderer::draw_interface(Racket racket1, Racket racket2) const
{
	draw_scores(racket1, racket2);
	draw_names(racket1, racket2);
	draw_line();
}

void Renderer::draw_scores(Racket racket1, Racket racket2) const
{
	if (racket1.get_side() == LEFT)
	{
		draw_left_score(racket1.get_score());
		draw_right_score(racket2.get_score());
	}
	else
	{
		draw_left_score(racket2.get_score());
		draw_right_score(racket1.get_score());
	}
}

void Renderer::draw_left_score(int score) const
{
	SDL_Rect dst;

	if (score <= 5)
	{
		dst.x = 1;
		dst.y = 1;
		dst.w = scores[score]->w;
		dst.h = scores[score]->h;
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, scores[score]);
		SDL_RenderCopy(renderer, texture, NULL, &dst);
	}
}

void Renderer::draw_right_score(int score) const
{
	SDL_Rect dst;

	if (score <= 5)
	{
		dst.x = SCREEN_WIDTH - scores[score]->w;
		dst.y = 1;
		dst.w = scores[score]->w;
		dst.h = scores[score]->h;
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, scores[score]);
		SDL_RenderCopy(renderer, texture, NULL, &dst);
	}
}

void Renderer::draw_names(Racket racket1, Racket racket2) const
{
	if (racket1.get_side() == LEFT)
	{
		draw_left_name(racket1.get_name());
		draw_right_name(racket2.get_name());
	}
	else
	{
		draw_left_name(racket2.get_name());
		draw_right_name(racket1.get_name());
	}
}

void Renderer::draw_left_name(std::string name) const
{
	SDL_Rect dst;

	SDL_Surface *text = TTF_RenderText_Solid(font, name.c_str(), color); 
	dst.x = 50;
	dst.y = 1;
	dst.w = text->w;
	dst.h = text->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text);
}

void Renderer::draw_right_name(std::string name) const
{
	SDL_Rect dst;

	SDL_Surface *text = TTF_RenderText_Solid(font, name.c_str(), color); 
	dst.x = SCREEN_WIDTH - text->w - 60;
	dst.y = 1;
	dst.w = text->w;
	dst.h = text->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text);
}

void Renderer::draw_line() const
{
	int x = 0;
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
	for (int x = 0; x <= SCREEN_WIDTH; x++)
		SDL_RenderDrawPoint(renderer, x, TOP_EDGE);
}

void Renderer::draw_ball(Ball ball) const
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);

	for (float radius = (float) ball.get_radius(); radius >= 0; radius -= 0.1)
		draw_circle(ball.get_location(), radius);
}

void Renderer::draw_circle(t_coord location, float radius) const
{
	int x,y;

	for (float a = 0; a < 2 * 3.14; a += 0.01)
	{
		x = cos(a) * radius + location.x;
		y = sin(a) * radius + location.y;
		SDL_RenderDrawPoint(renderer, x, y);
	}
}

void Renderer::draw_racket(Racket racket) const
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
	SDL_Rect racketrec = {racket.get_x(), racket.get_y(), RACKET_WIDTH, RACKET_HEIGHT};
	SDL_RenderFillRect(renderer, &racketrec);
}

void Renderer::render_waiting_room(Connexion conn, Racket racket1, Racket racket2, std::string name)
{
	if (conn.check_flags(PLAYER1) && !conn.is_setup_ready())
	{
		std::string line1 = "Waiting for another player";
		std::string line2 = "Player 1: " + name;

		clear_screen();
		render_text("Pong remote", {SCREEN_WIDTH / 2 - 5, 50});
		render_text(line1, {SCREEN_WIDTH / 2 -(int) line1.size()/2, 100});
		render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
		render_now();
	}
	else
	{
		std::string line1 = "The game is full. Push return when ready.";
		std::string line2 = "Player 1: " + racket1.get_name();
		std::string line3 = "Player 2: " + racket2.get_name();
		clear_screen();
		render_text(line1, {SCREEN_WIDTH / 2 - (int) line1.size()/2, 100});
		render_text(line2, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 150});
		render_text(line3, {SCREEN_WIDTH / 2 - (int) line2.size()/2, 200});
		render_now();
	}
}

void Renderer::render_end_game(Connexion conn, bool server_down)
{
	if (conn.check_flags(PLAYER_LEFT))
		render_text("Your opponent has left.", {SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT / 2});
	if (server_down = true)
		render_text("Server down", {SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT / 2 + 100});
	else if (conn.check_flags(SERVER_DISCONNECT))
		render_text("The server has shutdown.", {SCREEN_WIDTH/2 - 12, SCREEN_HEIGHT / 2});

	render_now();
}

void Renderer::render_winner(std::string name) const
{
	SDL_Rect dst;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	std::string message = "The winner is " + name;
	SDL_Surface *text = TTF_RenderText_Solid(font, message.c_str(), color); 
	dst.x = SCREEN_WIDTH / 2 - text->w / 2;
	dst.y = SCREEN_HEIGHT / 2;
	dst.w = text->w;
	dst.h = text->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text);
}

void Renderer::render_text(std::string str, t_coord location)
{
	SDL_Rect dst;

	SDL_Surface *text = TTF_RenderText_Solid(font, str.c_str(), color); 
	dst.x = location.x- text->w / 2;
	dst.y = location.y;
	dst.w = text->w;
	dst.h = text->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text);
}

void Renderer::render_now()
{
	SDL_RenderPresent(renderer);
}

void Renderer::clear_screen()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
}

void Renderer::cleanup()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	for (auto &surface : scores)
	{
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	scores.clear();
	TTF_CloseFont(font);
	TTF_Quit();
}
