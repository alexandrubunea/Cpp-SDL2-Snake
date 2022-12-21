#pragma once

#include <SDL.h>

class Game {
private:
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	const char* APPLICATION_NAME = "Snake Game";

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;

	bool game_running = true;
public:
	Game();
	~Game();
	void game_loop();
	void render();
};