#include <SDL.h>
#include <vector>

#include "Snake.h"
#include "Utils.h"
#include "Object.h"

Snake::Snake()
	: snake_direction(utils::directions::UP) {}
Snake::Snake(utils::vector2f pos)
	: snake_direction(utils::directions::UP) {
	snake_body.push_back(Object(pos, 25, 25));
}

void Snake::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (Object& obj : snake_body)
		obj.render(renderer);
}

void Snake::feed() {

}

void Snake::walk(float delta_time) {
	switch (snake_direction) {
		case utils::directions::UP: {
			snake_body[0].modify_y_by(-(delta_time * snake_speed));

			break;
		}
		case utils::directions::DOWN: {
			snake_body[0].modify_y_by(delta_time * snake_speed);

			break;
		}
		case utils::directions::LEFT: {
			snake_body[0].modify_x_by(-(delta_time * snake_speed));

			break;
		}
		case utils::directions::RIGHT: {
			snake_body[0].modify_x_by(delta_time * snake_speed);

			break;
		}
	}
}

void Snake::change_direction(utils::directions new_direction) {
	snake_direction = new_direction;
}

utils::directions& Snake::get_direction() {
	return snake_direction;
}