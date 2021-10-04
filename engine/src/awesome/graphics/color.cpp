#include "color.h"

#include <sstream>

Color::Color()
	: m_data({ 0.0f, 0.0f, 0.0f, 1.0f })
{
}

Color::Color(const int red, const int green, const int blue, const int alpha)
	: m_data()
{
	setRed(static_cast<float>(red / 255));
	setGreen(static_cast<float>(green / 255));
	setBlue(static_cast<float>(blue / 255));
	setAlpha(static_cast<float>(alpha / 255));
}

Color::Color(const float red, const float green, const float blue, const float alpha)
	: m_data({ red, green, blue, 1.0f })
{
}

bool Color::operator==(const Color& color) const
{
	return m_data == color.m_data;
}

bool Color::operator!=(const Color& color) const
{
	return m_data != color.m_data;
}

std::string Color::toString() const
{
	std::ostringstream format;
	format << "red:" << getRed() << ",green:" << getGreen() << ",blue:" << getBlue() << ",alpha:" << getAlpha();
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