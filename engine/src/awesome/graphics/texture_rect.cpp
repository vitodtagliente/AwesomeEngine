#include "texture_rect.h"

namespace graphics
{
	TextureRect::TextureRect()
		: x(0.0f)
		, y(0.0f)
		, width(1.0f)
		, height(1.0f)
	{

	}

	TextureRect::TextureRect(const float x, const float y, const float width, const float height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{

	}

	bool TextureRect::operator==(const TextureRect& rect) const
	{
		return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
	}

	bool TextureRect::operator!=(const TextureRect& rect) const
	{
		return x != rect.x || y != rect.y || width != rect.width || height != rect.height;
	}

	TextureRect::TextureRect(const TextureRect& rect)
		: x(rect.x)
		, y(rect.y)
		, width(rect.width)
		, height(rect.height)
	{
	}
}