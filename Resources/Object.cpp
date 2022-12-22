#include <SDL.h>

#include "Object.h"
#include "Utils.h"

Object::Object(utils::vector2f p_pos, float p_width, float p_height)
	:pos(p_pos), width(p_width), height(p_height) {
	
	rect.x = (int) pos.x;
	rect.y = (int) pos.y;
	rect.w = (int) width;
	rect.h = (int) height;

}

void Object::render(SDL_Renderer* renderer) {
	rect.x = (int) pos.x;
	rect.y = (int) pos.y;

	SDL_RenderFillRect(renderer, &rect);
}

void Object::modify_x_by(float modifier) {
	pos.x += modifier;
}

void Object::modify_y_by(float modifier) {
	pos.y += modifier;
}
