#pragma once

#include <string>
#include "../types.h"

/*
 * Color definition
 */

namespace awesome
{
	namespace data
	{
		struct Color
		{
			float red{ 0.0f };
			float green{ 0.0f };
			float blue{ 0.0f };
			float alpha{ 1.0f };

			Color() = default;
			Color(const uint n_red, const uint n_green, const uint n_blue);
			Color(const float n_red, const float n_green, const float n_blue, const float n_alpha = 1.0f);
			~Color() = default;

			Color(const Color& color);
			Color(Color&& color) = default;

			Color& operator= (const Color& color) = default;
			Color& operator=(Color&& color) = default;

			bool operator== (const Color& other) const;
			bool operator!= (const Color& other) const;

			Color operator+ (const Color& other) const;
			Color operator- (const Color& other) const;
			Color& operator+= (const Color& other);
			Color& operator-= (const Color& other);

			std::string toString() const;

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
}