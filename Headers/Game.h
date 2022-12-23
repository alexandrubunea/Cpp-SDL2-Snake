#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "Snake.h"

class Game {
private:
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	const char* APPLICATION_NAME = "Snake Game";

	const unsigned int SNAKE_SIZE = 40;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	bool game_running = true;

	Snake snake;

	unsigned int background_rows, background_cols;

	std::vector<SDL_Rect> background;
	SDL_Rect toolbar;
	const unsigned int TOOLBAR_HEIGHT = 40;

	utils::vector2f fruit;
	SDL_Rect fruit_rect;

	SDL_Surface* surface_score = NULL;
	SDL_Rect score_rect_dest;
	SDL_Texture* score_texture = NULL;
	TTF_Font* score_font = NULL;

	const unsigned int FONT_SCORE_SIZE = 15;

	unsigned int player_score = 0;

	enum GameState {
		NONE,
		GAME_RUNNING,
		GAME_OVER
	};

	GameState game_state;
public:
	Game();
	~Game();
	void game_loop();
	void render();
	void controller(SDL_Event& event);
};