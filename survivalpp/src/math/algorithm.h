/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <random>

namespace math
{
	const float pi = 3.1415927f;
	const float deg2rad_factor = pi / 180.0f;
	const float rad2deg_factor = 180.0f / pi;

	// degrees to radians
	inline float radians(const float t_theta)
	{
		return t_theta * deg2rad_factor;
	}
	// radians to degrees
	inline float degrees(const float t_theta)
	{
		return t_theta * rad2deg_factor;
	}

	template <typename T>
	T lerp(const T& t_a, const T& t_b, const float t_time) {
		return (1.0f - t_time) * t_a + t_b * t_time;
	}

	template <typename T>
	T clamp(const T& t_val, const T& t_min, const T& t_max) {
		return std::max(t_min, std::min(t_val, t_max));
	}

	inline int random(const int t_min, const int t_max)
	{
		static std::random_device r;
		static std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist(t_min, t_max);
		return uniform_dist(e1);
	}

	inline float random(const float t_min, const float t_max)
	{
		static std::random_device r;
		static std::default_random_engine e1(r());
		std::uniform_real_distribution<float> uniform_dist(t_min, t_max);
		return uniform_dist(e1);
	}

	inline float random()
	{
		return random(0.0f, 1.0f);
	}
}