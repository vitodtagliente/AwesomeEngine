#pragma once

namespace Awesome
{
	template <class T>
	struct tRect
	{
		T x{}, y{}, width{}, height{};

		tRect() {}
		tRect(T _width, T _height) {
			width = _width;
			height = _height;
		}
		tRect(T _x, T _y, T _width, T _height) {
			x = _x;
			y = _y;
			width = _width;
			height = _height;
		}
		tRect(const tRect& other) {
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
		}

		tRect<T>& operator= (const tRect<T>& other) {
			/* check for self-assignment */
			if (this == &other)
				return *this;

			/* copy */
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
			return *this;
		}

		bool operator== (const tRect& other) const {
			return (x == other.x && y == other.y &&
				width == other.width && height == other.height);
		}

		bool operator!= (const tRect& other) const {
			return (x != other.x || y != other.y ||
				width != other.width || height != other.height);
		}
	};

	typedef tRect<float> Rect;
	typedef tRect<int> iRect;
}