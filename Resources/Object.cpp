#include <SDL.h>

#include "Object.h"
#include "Utils.h"

Object::Object(utils::vector2f p_pos, float p_width, float p_height)
	:pos(p_pos), width(p_width), height(p_height) {
	
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = width;
	rect.h = height;

}

void Object::render(SDL_Renderer* renderer, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);
}
