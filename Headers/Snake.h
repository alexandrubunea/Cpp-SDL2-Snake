#pragma once

#include <SDL.h>
#include <vector>

#include "Utils.h"
#include "Object.h"

class Snake {
private:
	std::vector<Object> snake_body;
	utils::directions snake_direction;
	float snake_speed = 100.0f;
public:
	Snake();
	Snake(utils::vector2f pos);
	void render(SDL_Renderer* renderer);
	void feed();
	void walk(float delta_time);
	void change_direction(utils::directions new_direction);
	utils::directions& get_direction();
};