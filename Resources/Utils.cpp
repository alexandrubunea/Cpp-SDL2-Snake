#include <SDL.h>
#include <iostream>

#include "Utils.h"

void utils::print_sdl_error(const char* error_text) {
	std::cout << "[ERROR]: " << error_text << " | SDL_GetError(): " << SDL_GetError() << std::endl;
}

float utils::hire_time_in_seconds() {
	float t = SDL_GetTicks();
	t *= 0.001f;
	return t;
}

bool utils::vector2f::operator==(utils::vector2f aux) {
	return (int) x == (int) aux.x && (int) y == (int) aux.y;
}