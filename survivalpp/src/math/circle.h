/// Copyright (c) Vito Domenico Tagliente
#pragma once 

#include "vector2.h"

namespace math
{
	template <typename T>
	struct circle_t
	{
		union
		{
			struct
			{
				T x, y, radius;
			};

			T data[3];
		};

		const std::size_t length = 3;

		circle_t()
			: x()
			, y()
			, radius()
		{}

		circle_t(const vector2_t<T>& position, const T radius)
			: x(position.x)
			, y(position.y)
			, radius(radius)
		{

		}

		circle_t(const T x, const T y, const T radius)
			: x(x)
			, y(y)
			, radius(radius)
		{

		}

		circle_t(const circle_t& circle)
			: x(circle.x)
			, y(circle.y)
			, radius(circle.radius)
		{

		}

		circle_t& operator= (const circle_t& other)
		{
			x = other.x;
			y = other.y;
			radius = other.radius;
			return *this;
		}

		bool operator== (const circle_t& circle) const
		{
			return x == circle.x && y == circle.y && radius == circle.radius;
		}

		bool operator!= (const circle_t& circle) const
		{
			return !(*this == circle);
		}

		bool contains(const circle_t& circle) const
		{
			const T deltaX = x - circle.x;
			const T deltaY = y - circle.y;
			return static_cast<T>(sqrt(deltaX * deltaX + deltaY * deltaY)) <= radius
				&& circle.radius <= radius;
		}

		// return true if a point is contained inside the circle
		bool contains(const vector2_t<T>& point) const
		{
			const T deltaX = x - point.x;
			const T deltaY = y - point.y;
			return static_cast<T>(sqrt(deltaX * deltaX + deltaY * deltaY)) <= radius;
		}

		bool intersects(const circle_t& circle) const
		{
			const T deltaX = x - circle.x;
			const T deltaY = y - circle.y;
			return static_cast<T>(sqrt(deltaX * deltaX + deltaY * deltaY)) <= (radius + circle.radius);
		}
	};

	// circle types

	typedef circle_t<float> circle;
	typedef circle_t<int> circlei;
}