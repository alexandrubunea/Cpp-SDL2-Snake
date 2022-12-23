#include <SDL.h>
#include <SDL_ttf.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>

#include "Game.h"
#include "Utils.h"
#include "Object.h"

Game::Game()
	:background_rows(SCREEN_HEIGHT / SNAKE_SIZE), background_cols(SCREEN_WIDTH / SNAKE_SIZE), toolbar({ 0,0,0,0 }), fruit_rect({0, 0, 0, 0}), score_rect_dest({0, 0, 0, 0}) {
	
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		utils::print_sdl_error("An error occured while trying to init sdl video.");
		SDL_Quit();
		return;
	}
	
	window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		utils::print_sdl_error("An error occured while trying to create the window.");
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		utils::print_sdl_error("An error occured while trying to create the renderer.");
		SDL_Quit();
		return;
	}

	if (TTF_Init() == -1)
		utils::print_sdl_error("An error occured while trying to use TTF_Init().");

	score_font = TTF_OpenFont("arial.ttf", FONT_SCORE_SIZE);
	if (score_font == NULL)
		utils::print_sdl_error("An error occured while trying to load the score font.");

	snake = Snake(utils::vector2f(200, 200), (float) SNAKE_SIZE);

	SDL_Rect square;
	square.w = square.h = SNAKE_SIZE;
	unsigned int x = 0, y = 0;
	for (unsigned int i = 0; i < background_rows; ++i) {
		x = (i & 1) ? 0 : SNAKE_SIZE;
		square.y = y;

		for (unsigned int j = (i & 1) ? 0 : 1; j < background_cols; ++j) {
			square.x = x;

			background.push_back(square);

			x += SNAKE_SIZE * 2;
		}

		y += SNAKE_SIZE;
	}

	toolbar.x = toolbar.y = 0;
	toolbar.w = SCREEN_WIDTH;
	toolbar.h = TOOLBAR_HEIGHT;

	srand((unsigned int) time(NULL));

	fruit.x = (float) (rand() % (background_cols - 1));
	fruit.y = (float) (rand() % (background_rows - 1) + (TOOLBAR_HEIGHT / SNAKE_SIZE));

	fruit_rect.x = (int) (fruit.x * SNAKE_SIZE);
	fruit_rect.y = (int) (fruit.y * SNAKE_SIZE);
	fruit_rect.w = fruit_rect.h = SNAKE_SIZE;

	surface_score = TTF_RenderText_Solid(score_font, "", { 255, 255, 255 });
	score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);

	score_rect_dest.x = 20;
	score_rect_dest.y = TOOLBAR_HEIGHT / 2 - FONT_SCORE_SIZE;
	score_rect_dest.h = 20;
	score_rect_dest.w = 0;

	game_loop();

	SDL_Quit();
	TTF_CloseFont(score_font);
	TTF_Quit();
}
Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::game_loop() {

	const float delta_time = 0.1f;

	float current_time = utils::hire_time_in_seconds(),
		accumulator = 0.0f;

	SDL_Event event;

	while (game_running) {

		float new_time = utils::hire_time_in_seconds(),
			frame_time = new_time - current_time;
		current_time = new_time;
		
		accumulator += frame_time;

		while (accumulator >= delta_time) {

			controller(event);

			snake.walk(SCREEN_WIDTH, SCREEN_HEIGHT, TOOLBAR_HEIGHT);

			if (snake.get_head().get_pos() == utils::vector2f((float) fruit_rect.x, (float) fruit_rect.y)) {

				snake.feed();

				bool is_valid_position = false;
				std::vector<Object> snake_tail = snake.get_snake_body();

				while (!is_valid_position) {
					is_valid_position = true;

					fruit.x = (float)(rand() % (background_cols - 1));
					fruit.y = (float)(rand() % (background_rows - 1) + (TOOLBAR_HEIGHT / SNAKE_SIZE));

					for (unsigned int i = 0; i < snake_tail.size(); ++i)
						if (snake_tail[i].get_pos() == utils::vector2f((float) (fruit.x * SNAKE_SIZE), (float) (fruit.y * SNAKE_SIZE)))
							is_valid_position = false;
				}

				fruit_rect.x = (int) (fruit.x * SNAKE_SIZE);
				fruit_rect.y = (int) (fruit.y * SNAKE_SIZE);

				++player_score;

				std::string score_str = "YOUR SCORE: " + std::to_string(player_score);

				SDL_FreeSurface(surface_score);
				surface_score = TTF_RenderText_Solid(score_font, score_str.c_str(), { 255, 255, 255 });
				
				SDL_DestroyTexture(score_texture);
				score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);

				score_rect_dest.w = score_str.size() * FONT_SCORE_SIZE;
			}

			accumulator -= delta_time;
		}

		render();
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);

	SDL_RenderClear(renderer);

	// Background
	SDL_SetRenderDrawColor(renderer, 58, 180, 73, 255);
	for (unsigned int i = 0; i < background.size(); ++i)
		SDL_RenderFillRect(renderer, &background[i]);

	// Toolbar
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderFillRect(renderer, &toolbar);

	// Fruit
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &fruit_rect);

	// Snake
	snake.render(renderer);

	// Score
	SDL_RenderCopy(renderer, score_texture, NULL, &score_rect_dest);

	SDL_RenderPresent(renderer);
}

void Game::controller(SDL_Event& event) {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			game_running = false;
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_w: {
					if (snake.get_head_direction() == utils::directions::DOWN) break;

					snake.change_head_direction(utils::directions::UP);

					break;
				}
				case SDLK_s: {
					if (snake.get_head_direction() == utils::directions::UP) break;

					snake.change_head_direction(utils::directions::DOWN);

					break;
				}
				case SDLK_a: {
					if (snake.get_head_direction() == utils::directions::RIGHT) break;

					snake.change_head_direction(utils::directions::LEFT);

					break;
				}
				case SDLK_d: {
					if (snake.get_head_direction() == utils::directions::LEFT) break;

					snake.change_head_direction(utils::directions::RIGHT);

					break;
				}
				case SDLK_f: {
					snake.feed();
					break;
				}
			}
		}
	}
}