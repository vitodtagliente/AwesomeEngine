#include <awesome/data/color.h>
#include <algorithm>

namespace awesome
{
	namespace data
	{
		Color::Color(const uint n_red, const uint n_green, const uint n_blue) {
			red = static_cast<float>(n_red) / 255.0f;
			green = static_cast<float>(n_green) / 255.0f;
			blue = static_cast<float>(n_blue) / 255.0f;
			alpha = 1.0f;
		}
		
		Color::Color(const float n_red, const float n_green, const float n_blue, const float n_alpha /*= 1.0f*/) {
			red = n_red;
			green = n_green;
			blue = n_blue;
			alpha = n_alpha;
		}

		Color::Color(const Color& color)
		{
			red = color.red;
			green = color.green;
			blue = color.blue;
			alpha = color.alpha;
		}

		bool Color::operator== (const Color& other) const
		{
			return red == other.red &&
				green == other.green &&
				blue == other.blue &&
				alpha == other.alpha;
		}

		bool Color::operator!= (const Color& other) const
		{
			return !(*this == other);
		}

		Color Color::operator+ (const Color& other) const
		{
			return 
			{
				std::min(red + other.red, 1.0f),
				std::min(green + other.green, 1.0f),
				std::min(blue + other.blue, 1.0f),
				std::min(alpha + other.alpha, 1.0f)
			};
		}

		Color Color::operator- (const Color& other) const
		{
			return
			{
				std::max(red - other.red, -1.0f),
				std::max(green - other.green, -1.0f),
				std::max(blue - other.blue, -1.0f),
				std::max(alpha - other.alpha, -1.0f)
			};
		}

		Color& Color::operator+= (const Color& other) {
			red = std::min(red + other.red, 1.0f);
			green = std::min(green + other.green, 1.0f);
			blue = std::min(blue + other.blue, 1.0f);
			alpha = std::min(alpha + other.alpha, 1.0f);
			return *this;
		}

		Color& Color::operator-= (const Color& other) {
			red = std::max(red - other.red, -1.0f);
			green = std::max(green - other.green, -1.0f);
			blue = std::max(blue - other.blue, -1.0f);
			alpha = std::max(alpha - other.alpha, -1.0f);
			return *this;
		}

		std::string Color::toString() const
		{
			return "Red:" + std::to_string(red)
				+ ", Green:" + std::to_string(green)
				+ ", Blue:" + std::to_string(blue)
				+ ", Alpha:" + std::to_string(alpha);
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
}