#pragma once

namespace utils {
	void print_sdl_error(const char* error_text);
	int hire_time_in_seconds();

	struct vector2f {
		float x, y;
		vector2f() : x(0.0f), y(0.0f) {}
		vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}
	};
};