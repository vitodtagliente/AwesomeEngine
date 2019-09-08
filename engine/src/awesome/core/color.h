#pragma once

#include <string>
#include "types.h"

namespace awesome
{
	struct Color final
	{
		Color();
		Color(const uint8 t_red, const uint8 t_green, const uint8 t_blue);
		Color(const float t_red, const float t_green, const float t_blue, const float t_alpha = 1.0f);
		~Color();

		Color(const Color& t_color) = default;
		Color(Color&& t_color) = default;
		Color& operator= (const Color& t_color) = default;
		Color& operator=(Color&& t_color) = default;

		bool operator== (const Color& t_color) const;
		bool operator!= (const Color& t_color) const;

		Color operator+ (const Color& t_color) const;
		Color operator- (const Color& t_color) const;
		Color& operator+= (const Color& t_color);
		Color& operator-= (const Color& t_color);

		std::string toString() const;

		float red;
		float green;
		float blue;
		float alpha;

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