#pragma once 

#include "vector2.h"

namespace awesome
{
	template <typename T>
	struct circle_t
	{
		vector2_t<T> position;
		T radius;

		circle_t()
			: position()
			, radius()
		{}

		circle_t(const vector2_t& t_position, const T t_radius)
			: position(t_position)
			, radius(t_radius)
		{

		}

		circle_t(const T t_x, const T t_y, const T t_radius)
			: position(t_x, t_y)
			, radius(t_radius)
		{

		}

		circle_t(const circle_t& t_circle)
			: position(t_circle.position)
			, radius(t_circle.radius)
		{

		}

		bool operator== (const circle_t& t_circle) const
		{
			return position == t_circle.position
				&& radius == t_circle.radius;
		}

		bool operator!= (const circle_t& t_circle) const
		{
			return !(*this == t_circle);
		}

		bool intersects(const circle_t& t_circle) const
		{
			return position.distance(t_circle.position) < (radius + t_circle.radius);
		}

		// return true if a point is contained inside the circle
		bool intersects(const vector2_t& t_point) const
		{
			return position.distance(t_point) <= radius;
		}

	};

	// circle types

	typedef circle_t<float> circle;
}