#include "color.h"

#include <vdtmath/algorithm.h>

namespace graphics
{
	Color::Color()
		: red()
		, green()
		, blue()
		, alpha(1.0f)
	{
	}

	Color::Color(const int red, const int green, const int blue, const int alpha)
		: red(math::clamp(static_cast<float>(red) / 255, 0.0f, 1.0f))
		, green(math::clamp(static_cast<float>(green) / 255, 0.0f, 1.0f))
		, blue(math::clamp(static_cast<float>(blue) / 255, 0.0f, 1.0f))
		, alpha(math::clamp(static_cast<float>(alpha) / 255, 0.0f, 1.0f))
	{
	}

	Color::Color(const float red, const float green, const float blue, const float alpha)
		: red(math::clamp(red, 0.0f, 1.0f))
		, green(math::clamp(green, 0.0f, 1.0f))
		, blue(math::clamp(blue, 0.0f, 1.0f))
		, alpha(math::clamp(alpha, 0.0f, 1.0f))
	{
	}

	bool Color::operator==(const Color& color) const
	{
		return red == color.red && green == color.green && blue == color.blue && alpha == color.alpha;
	}

	bool Color::operator!=(const Color& color) const
	{
		return red != color.red || green != color.green || blue != color.blue || alpha != color.alpha;
	}

	const Color Color::White(1.0f, 1.0f, 1.0f);
	const Color Color::Black(0.0f, 0.0f, 0.0f);
	const Color Color::Red(1.0f, 0.0f, 0.0f);
	const Color Color::Green(0.0f, 1.0f, 0.0f);
	const Color Color::Blue(0.0f, 0.0f, 1.0f);
	const Color Color::Cyan(0.0f, 1.0f, 1.0f);
	const Color Color::Yellow(1.0f, 1.0f, 0.0f);
	const Color Color::Magenta(1.0f, 0.0f, 1.0f);
	const Color Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);
}