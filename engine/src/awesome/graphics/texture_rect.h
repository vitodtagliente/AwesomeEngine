/// Copyright (c) Vito Domenico Tagliente
#pragma once

class TextureRect
{
	union
	{
		struct
		{
			float x, y, width, height;
		};

		float data[4];
	};

	TextureRect()
		: x(0.0f)
		, y(0.0f)
		, width(1.0f)
		, height(1.0f)
	{

	}

	TextureRect(const float x, const float y, const float width, const float height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{

	}

	TextureRect(const TextureRect& rect)
		: x(rect.x)
		, y(rect.y)
		, width(rect.width)
		, height(rect.height)
	{
	}
};