/// Copyright (c) Vito Domenico Tagliente
#pragma once
#pragma warning(disable : 4201)

namespace graphics
{
	class TextureRect
	{
	public:

		union
		{
			struct
			{
				float x, y, width, height;
			};

			float data[4];
		};

		TextureRect();
		TextureRect(float x, float y, float width, float height);
		TextureRect(const TextureRect& rect);
		~TextureRect() = default;

		TextureRect(TextureRect&& rect) = default;
		TextureRect& operator= (const TextureRect& rect) = default;
		TextureRect& operator=(TextureRect&& rect) = default;

		bool operator== (const TextureRect& rect) const;
		bool operator!= (const TextureRect& rect) const;
	};
}