/// Copyright (c) Vito Domenico Tagliente
#pragma once
#pragma warning(disable : 4201)

#include <array>
#include <string>

namespace graphics
{
	class Color
	{
	public:

		union
		{
			struct
			{
				float red, green, blue, alpha;
			};

			float data[4];
		};

		Color();
		Color(int red, int green, int blue, int alpha = 255);
		Color(float red, float green, float blue, float alpha = 1.0f);
		~Color() = default;

		Color(const Color& color) = default;
		Color(Color&& color) = default;
		Color& operator= (const Color& color) = default;
		Color& operator=(Color&& color) = default;

		bool operator== (const Color& color) const;
		bool operator!= (const Color& color) const;

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Cyan;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Transparent;

	};
}