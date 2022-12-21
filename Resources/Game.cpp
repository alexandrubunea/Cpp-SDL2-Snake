#include <SDL.h>

#include "Game.h"
#include "Utils.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		utils::print_sdl_error("An error occured while trying to init sdl video.");
	
	window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
		utils::print_sdl_error("An error occured while trying to create the window.");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		utils::print_sdl_error("An error occured while trying to create the renderer.");
	SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255);

	game_loop();
}
Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::game_loop() {

	const float delta_time = 0.01f;

	float current_time = utils::hire_time_in_seconds(),
		accumulator = 0.0f;

	while (game_running) {

		float new_time = utils::hire_time_in_seconds(),
			frame_time = new_time - current_time;
		current_time = new_time;
		
		accumulator += frame_time;

		while (accumulator >= delta_time) {

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					game_running = false;
			}

			accumulator -= delta_time;
		}

		render();
	}

	SDL_Quit();
}

void Game::render() {
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}