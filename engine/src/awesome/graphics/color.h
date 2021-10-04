/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <array>
#include <string>

class Color
{
public:
	Color();
	Color(int red, int green, int blue, int alpha = 255);
	Color(float red, float green, float blue, float alpha = 1.0f);
	~Color() = default;

	Color(const Color& color) = default;
	Color(Color&& color) = default;
	Color& operator= (const Color& color) = default;
	Color& operator=(Color&& color) = default;

	float getRed() const { return m_data[0]; }
	float getGreen() const { return m_data[1]; }
	float getBlue() const { return m_data[2]; }
	float getAlpha() const { return m_data[3]; }

	void setRed(float value) { m_data[0] = value; }
	void setGreen(float value) { m_data[1] = value; }
	void setBlue(float value) { m_data[2] = value; }
	void setAlpha(float value) { m_data[3] = value; }

	const std::array<float, 4>& getData() const { return m_data; }
	std::array<float, 4>& getData() { return m_data; }

	bool operator== (const Color& color) const;
	bool operator!= (const Color& color) const;

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

private:
	std::array<float, 4> m_data;
};