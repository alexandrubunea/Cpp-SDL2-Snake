#pragma once

#include <SDL.h>

#include "Utils.h"

class Object {
private:
	utils::vector2f pos;
	float width, height;
	SDL_Rect rect;
public:
	Object(utils::vector2f p_pos, float p_width, float p_height);
	void render(SDL_Renderer* renderer);
	void modify_x_by(float modifier);
	void modify_y_by(float modifier);
	void set_pos(utils::vector2f new_pos);
	utils::vector2f& get_pos();
};