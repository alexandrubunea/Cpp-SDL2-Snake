#include <SDL.h>
#include <iostream>

#include "Utils.h"

void utils::print_sdl_error(const char* error_text) {
	std::cout << "[ERROR]: " << error_text << " | SDL_GetError(): " << SDL_GetError() << std::endl;
}

int utils::hire_time_in_seconds() {
	return SDL_GetTicks();
}

void utils::print(const char* text) {
	std::cout << text << std::endl;
}