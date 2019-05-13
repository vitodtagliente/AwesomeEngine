#pragma once

#include <cmath>

namespace awesome
{
	const float pi = 3.1415927f;
	const float deg2rad_factor = pi / 180.0f;
	const float rad2deg_factor = 180.0f / pi;

	// degrees to radians
	float radians(const float theta) {
		return theta * deg2rad_factor;
	}

	// radians to degrees
	float degrees(const float theta) {
		return theta * rad2deg_factor;
	}

	template <typename T>
	T lerp(const T& a, const T& b, const float t) {
		return (1.0f - t) * a + b * t;
	}

	template <typename T>
	T clamp(const T& val, const T& min, const T& max) {
		return std::max(min, std::min(val, max));
	}
};