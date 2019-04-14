#include "color.h"
#include <algorithm>

namespace awesome
{
	Color::Color()
		: red()
		, green()
		, blue()
		, alpha()
	{
	}

	Color::Color(const uint8 t_red, const uint8 t_green, const uint8 t_blue)
		: alpha(1.0f)
	{
		red = static_cast<float>(t_red) / 255.0f;
		green = static_cast<float>(t_green) / 255.0f;
		blue = static_cast<float>(t_blue) / 255.0f;
	}

	Color::Color(const float t_red, const float t_green, const float t_blue, const float t_alpha)
		: red(t_red)
		, green(t_green)
		, blue(t_blue)
		, alpha(t_alpha)
	{
	}

	Color::Color(const std::string t_hecadeximal)
	{
		// #todo: to be implemented
	}

	Color::~Color()
	{
	}

	bool Color::operator==(const Color& t_color) const
	{
		return red == t_color.red &&
			green == t_color.green &&
			blue == t_color.blue &&
			alpha == t_color.alpha;
	}

	bool Color::operator!=(const Color& t_color) const
	{
		return !(*this == t_color);
	}

	Color Color::operator+(const Color& t_color) const
	{
		return {
			std::min(red + t_color.red, 1.0f),
			std::min(green + t_color.green, 1.0f),
			std::min(blue + t_color.blue, 1.0f),
			std::min(alpha + t_color.alpha, 1.0f),
		};
	}

	Color Color::operator-(const Color& t_color) const
	{
		return {
			std::max(red + t_color.red, 0.0f),
			std::max(green + t_color.green, 0.0f),
			std::max(blue + t_color.blue, 0.0f),
			std::max(alpha + t_color.alpha, 0.0f),
		};
	}

	Color& Color::operator+=(const Color& t_color)
	{
		red = std::min(red + t_color.red, 1.0f);
		green = std::min(green + t_color.green, 1.0f);
		blue = std::min(blue + t_color.blue, 1.0f);
		alpha = std::min(alpha + t_color.alpha, 1.0f);
		return *this;
	}

	Color& Color::operator-=(const Color& t_color)
	{
		red = std::max(red + t_color.red, 0.0f);
		green = std::max(green + t_color.green, 0.0f);
		blue = std::max(blue + t_color.blue, 0.0f);
		alpha = std::max(alpha + t_color.alpha, 0.0f);
		return *this;
	}

	std::string Color::toString() const
	{
		return "color {r: " + std::to_string(red) +
			", g: " + std::to_string(green) +
			", b: " + std::to_string(blue) +
			", a: " + std::to_string(alpha) + " }";
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