#pragma once

namespace awesome
{
	namespace math
	{
		const float pi = 3.1415927f;
		const float deg2rad_factor = pi / 180.0f;
		const float rad2deg_factor = 180.0f / pi;

		// degrees to radians
		float radians(const float t_theta);
		// radians to degrees
		float degrees(const float t_theta);

		template <typename T>
		T lerp(const T& t_a, const T& t_b, const float t_time) {
			return (1.0f - t_time) * t_a + t_b * t_time;
		}

		template <typename T>
		T clamp(const T & t_val, const T & t_min, const T & t_max) {
			return std::max(t_min, std::min(t_val, t_max));
		}
	}
}