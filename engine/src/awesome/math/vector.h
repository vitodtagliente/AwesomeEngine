#pragma once

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace awesome
{
	template <typename T>
	vector3_t<T> to_vector3(const vector2_t<T>& t_vector)
	{
		return { t_vector.x, t_vector.y, static_cast<T>(0.0) };
	}

	template <typename T>
	vector3_t<T> to_vec3(const vector2_t<T>& t_vector)
	{
		return { t_vector.x, t_vector.y, static_cast<T>(0.0) };
	}

	template <typename T>
	vector4_t<T> to_vector4(const vector2_t<T>& t_vector)
	{
		return { t_vector.x, t_vector.y, static_cast<T>(0.0), static_cast<T>(0.0) };
	}

	template <typename T>
	vector4_t<T> to_vector4(const vector3_t<T>& t_vector)
	{
		return { t_vector.x, t_vector.y, t_vector.z, static_cast<T>(0.0) };
	}

	template <typename T>
	vector4_t<T> to_vec4(const vector2_t<T>& t_vector)
	{
		return { t_vector.x, t_vector.y, static_cast<T>(0.0), static_cast<T>(0.0) };
	}

	template <typename T>
	vector4_t<T> to_vec4(const vector3_t<T>& t_vector)
	{
		return { t_vector.x, t_vector.y, t_vector.z, static_cast<T>(0.0) };
	}
}