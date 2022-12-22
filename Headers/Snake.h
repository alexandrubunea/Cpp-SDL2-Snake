#pragma once

#include <SDL.h>
#include <vector>

#include "Utils.h"
#include "Object.h"

class Snake {
private:
	std::vector<Object> snake_body;
	float snake_speed = 0.0f;
	float snake_size = 0.0f;
public:
	Snake();
	Snake(utils::vector2f pos, float p_snake_size);
	void render(SDL_Renderer* renderer);
	void feed();
	void walk(unsigned int width, unsigned int height);
	void change_head_direction(utils::directions new_direction);
	utils::directions& get_head_direction();
	Object& get_head();
};