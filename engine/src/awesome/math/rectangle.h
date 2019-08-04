#pragma once 

#include "vector2.h"

namespace awesome
{
	template <typename T>
	struct rectangle_t
	{
		T x, y, width, height;

		rectangle_t()
			: x()
			, y()
			, width()
			, height()
		{}

		rectangle_t(const T t_x, const T t_y, const T t_width, const T t_height)
			: x(t_x)
			, y(t_y)
			, width(t_width)
			, height(t_height)
		{

		}

		bool operator== (const rectangle_t& t_other) const
		{
			return x == t_other.x && y == t_other.y
				&& width == t_other.width && height == t_other.height;
		}

		bool operator!= (const rectangle_t& t_other) const
		{
			return !(*this == t_other);
		}

		rectangle_t& operator*= (const T t_scalar)
		{
			x *= t_scalar;
			y *= t_scalar;
			width *= t_scalar;
			height *= t_scalar;
			return *this;
		}

		rectangle_t& operator/= (const T t_scalar)
		{
			const T factor = static_cast<T>(1) / t_scalar;
			x *= factor;
			y *= factor;
			width *= factor;
			height *= factor;
			return *this;
		}

		rectangle_t operator* (const T t_scalar)
		{
			return 
			{ 
				x * t_scalar, 
				y * t_scalar, 
				width * t_scalar, 
				height * t_scalar 
			};
		}

		rectangle_t operator/ (const T t_scalar)
		{
			const T factor = static_cast<T>(1) / t_scalar;
			return
			{
				x * factor,
				y * factor,
				width * factor,
				height * factor
			};
		}

		bool intersects(const rectangle_t& t_other) const
		{
			// #todo
			return false;
		}

	};

	// rectangle types

	typedef rectangle_t<float> rect;
	typedef rect rectangle;
}