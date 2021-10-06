#include "color.h"

#include <sstream>

Color::Color()
	: red()
	, green()
	, blue()
	, alpha(1.0f)
{
}

Color::Color(const int red, const int green, const int blue, const int alpha)
	: red(red / 255)
	, green(green / 255)
	, blue(blue / 255)
	, alpha(alpha)
{
}

Color::Color(const float red, const float green, const float blue, const float alpha)
	: red(red)
	, green(green)
	, blue(blue)
	, alpha(alpha)
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

std::string Color::toString() const
{
	std::ostringstream format;
	format << "red:" << red << ",green:" << green << ",blue:" << blue << ",alpha:" << alpha;
	return format.str();
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