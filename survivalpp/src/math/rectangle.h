/// Copyright (c) Vito Domenico Tagliente
#pragma once 

#include "vector2.h"

namespace math
{
	template <typename T>
	struct rectangle_t
	{
		union
		{
			struct
			{
				T x, y, width, height;
			};

			T data[4];
		};

		const std::size_t length = 4;

		rectangle_t()
			: x()
			, y()
			, width()
			, height()
		{}

		rectangle_t(const vector2_t<T>& position, const T width, const T height)
			: x(position.x)
			, y(position.y)
			, width(width)
			, height(height)
		{

		}

		rectangle_t(const T x, const T y, const T width, const T height)
			: x(x)
			, y(y)
			, width(width)
			, height(height)
		{

		}

		rectangle_t(const rectangle_t& rect)
			: x(rect.x)
			, y(rect.y)
			, width(rect.width)
			, height(rect.height)
		{

		}

		rectangle_t& operator= (const rectangle_t& other)
		{
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
			return *this;
		}

		bool operator== (const rectangle_t& rect) const
		{
			return x == rect.x && y == rect.y
				&& width == rect.width && height == rect.height;
		}

		bool operator!= (const rectangle_t& rect) const
		{
			return !(*this == rect);
		}

		bool contains(const rectangle_t& rect) const
		{
			return x - width <= rect.x - width
				&& rect.x + rect.width <= x + width
				&& y - height <= rect.y - rect.height
				&& rect.y + rect.height <= y + height;
		}

		bool contains(const vector2_t<T>& point) const
		{
			return point.x >= x - width
				&& point.x <= x + width
				&& point.y >= y - height
				&& point.y <= y + height;
		}

		bool intersects(const rectangle_t& rect) const
		{
			return !(x - width > rect.x + rect.width
				|| x + width < rect.x - rect.width
				|| y - height > rect.y + rect.height
				|| y + height < rect.y - height);
		}
	};

	// rectangle types

	typedef rectangle_t<float> rect;
	typedef rect rectangle;
	typedef rectangle_t<int> recti;
	typedef recti rectanglei;
}