/// Copyright (c) Vito Domenico Tagliente
#pragma once
#pragma warning(disable : 4201)

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
			: x(), y(), width(), height()
		{

		}

		rectangle_t(const T x, const T y, const T width, const T height)
			: x(x), y(y), width(width), height(height)
		{

		}

		rectangle_t(const rectangle_t& other)
		{
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
		}

		std::size_t size() const
		{
			return length;
		}

		rectangle_t& operator= (const rectangle_t& other)
		{
			// check for self-assignment
			if (this == &other)
				return *this;

			// copy 
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
			return *this;
		}

		bool operator== (const rectangle_t& other) const
		{
			return x == other.x && y == other.y && width == other.width && height == other.height;
		}

		bool operator!= (const rectangle_t& other) const
		{
			return !(*this == other);
		}
	};

	typedef rectangle_t<float> rect;
	typedef rectangle_t<int> recti;
}