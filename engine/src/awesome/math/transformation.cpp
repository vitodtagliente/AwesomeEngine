#include "transformation.h"

namespace awesome
{
	base_matrix<4, 4, float> orthographic(
		const float t_left, 
		const float t_right,
		const float t_bottom, 
		const float t_top,
		const float t_near_plane, 
		const float t_far_plane)
	{
		base_matrix<4, 4, float> m = identity<4, float>();

		m(0, 0) = 2.0f / (t_right - t_left);
		m(1, 1) = 2.0f / (t_top - t_bottom);
		m(2, 2) = -2.0f / (t_far_plane - t_near_plane);

		m(3, 0) = -(t_right + t_left) / (t_right - t_left);
		m(3, 1) = -(t_top + t_bottom) / (t_top - t_bottom);
		m(3, 2) = -(t_far_plane + t_near_plane) / (t_far_plane - t_near_plane);

		return m;
	}

	// perspective projection
	base_matrix<4, 4, float> perspective(
		const float t_fov, 
		const float t_aspect,
		const float t_near_plane, 
		const float t_far_plane)
	{
		base_matrix<4, 4, float> m(0.0f);

		float top = t_near_plane * std::tan(t_fov / 2.0f);
		float bottom = -top;
		float right = top * t_aspect;
		float left = -top * t_aspect;

		m(0, 0) = (2.0f * t_near_plane) / (right - left);
		m(1, 1) = (2.0f * t_near_plane) / (top - bottom);
		m(2, 2) = -(t_far_plane + t_near_plane) / (t_far_plane - t_near_plane);

		m(2, 3) = -1.0f;
		m(3, 2) = -(2.0f * t_near_plane * t_far_plane) / (t_far_plane - t_near_plane);

		return m;
	}
}