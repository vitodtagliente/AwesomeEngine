#pragma once 

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

	};

	// rectangle types

	typedef rectangle_t<float> rect;
	typedef rect rectangle;
}