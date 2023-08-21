#include "color.h"

#include "math/algorithm.h"

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

	Color Color::random()
	{
		return Color(
			math::random(0.f, 1.f),
			math::random(0.f, 1.f),
			math::random(0.f, 1.f),
			math::random(0.f, 1.f)
		);
	}

	Color Color::random(const Color& color1, const Color& color2)
	{
		if (color1 == color2) return color1;

		return Color(
			(color2.red > color2.red) ? math::random(color1.red, color2.red) : math::random(color2.red, color1.red),
			(color2.green > color2.green) ? math::random(color1.green, color2.green) : math::random(color2.green, color1.green),
			(color2.blue > color2.blue) ? math::random(color1.blue, color2.blue) : math::random(color2.blue, color1.blue),
			(color2.alpha > color2.alpha) ? math::random(color1.alpha, color2.alpha) : math::random(color2.alpha, color1.alpha)
		);
	}

	const Color Color::Red(1.0f, 0.0f, 0.0f);
	const Color Color::Green(0.0f, 1.0f, 0.0f);
	const Color Color::Blue(0.0f, 0.0f, 1.0f);
	const Color Color::Yellow(1.0f, 1.0f, 0.0f);
	const Color Color::Cyan(0.0f, 1.0f, 1.0f);
	const Color Color::Magenta(1.0f, 0.0f, 1.0f);
	const Color Color::White(1.0f, 1.0f, 1.0f);
	const Color Color::Black(0.0f, 0.0f, 0.0f);
	const Color Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);

	const Color Color::Gray05(0.05f, 0.05f, 0.05f, 1.f);
	const Color Color::Gray10(0.10f, 0.10f, 0.10f, 1.f);
	const Color Color::Gray15(0.15f, 0.15f, 0.15f, 1.f);
	const Color Color::Gray20(0.20f, 0.20f, 0.20f, 1.f);
	const Color Color::Gray25(0.25f, 0.25f, 0.25f, 1.f);
	const Color Color::Gray30(0.30f, 0.30f, 0.30f, 1.f);
	const Color Color::Gray35(0.35f, 0.35f, 0.35f, 1.f);
	const Color Color::Gray40(0.40f, 0.40f, 0.40f, 1.f);
	const Color Color::Gray45(0.45f, 0.45f, 0.45f, 1.f);
	const Color Color::Gray50(0.50f, 0.50f, 0.50f, 1.f);
	const Color Color::Gray55(0.55f, 0.55f, 0.55f, 1.f);
	const Color Color::Gray60(0.60f, 0.60f, 0.60f, 1.f);
	const Color Color::Gray65(0.65f, 0.65f, 0.65f, 1.f);
	const Color Color::Gray70(0.70f, 0.70f, 0.70f, 1.f);
	const Color Color::Gray75(0.75f, 0.75f, 0.75f, 1.f);
	const Color Color::Gray80(0.80f, 0.80f, 0.80f, 1.f);
	const Color Color::Gray85(0.85f, 0.85f, 0.85f, 1.f);
	const Color Color::Gray90(0.90f, 0.90f, 0.90f, 1.f);
	const Color Color::Gray95(0.95f, 0.95f, 0.95f, 1.f);

	const Color Color::DimGray(0.329412f, 0.329412f, 0.329412f, 1.f);
	const Color Color::Gray(0.752941f, 0.752941f, 0.752941f, 1.f);
	const Color Color::LightGray(0.658824f, 0.658824f, 0.658824f, 1.f);
	const Color Color::VLightGray(0.80f, 0.80f, 0.80f, 1.f);

	const Color Color::Aquamarine(0.439216f, 0.858824f, 0.576471f, 1.f);
	const Color Color::BlueViolet(0.62352f, 0.372549f, 0.0623529f, 1.f);
	const Color Color::Brown(0.647059f, 0.164706f, 0.164706f, 1.f);
	const Color Color::CadetBlue(0.372549f, 0.623529f, 0.623529f, 1.f);
	const Color Color::Coral(1.0f, 0.498039f, 0.0f, 1.f);
	const Color Color::CornflowerBlue(0.258824f, 0.258824f, 0.435294f, 1.f);
	const Color Color::DarkGreen(0.184314f, 0.309804f, 0.184314f, 1.f);
	const Color Color::DarkOliveGreen(0.309804f, 0.309804f, 0.184314f, 1.f);
	const Color Color::DarkOrchid(0.6f, 0.196078f, 0.8f, 1.f);
	const Color Color::DarkSlateBlue(0.419608f, 0.137255f, 0.556863f, 1.f);
	const Color Color::DarkSlateGray(0.184314f, 0.309804f, 0.309804f, 1.f);
	const Color Color::DarkTurquoise(0.439216f, 0.576471f, 0.858824f, 1.f);
	const Color Color::Firebrick(0.556863f, 0.137255f, 0.137255f, 1.f);
	const Color Color::ForestGreen(0.137255f, 0.556863f, 0.137255f, 1.f);
	const Color Color::Gold(0.8f, 0.498039f, 0.196078f, 1.f);
	const Color Color::Goldenrod(0.858824f, 0.858824f, 0.439216f, 1.f);
	const Color Color::GreenYellow(0.576471f, 0.858824f, 0.439216f, 1.f);
	const Color Color::IndianRed(0.309804f, 0.184314f, 0.184314f, 1.f);
	const Color Color::Khaki(0.623529f, 0.623529f, 0.372549f, 1.f);
	const Color Color::LightBlue(0.74902f, 0.847059f, 0.847059f, 1.f);
	const Color Color::LightSteelBlue(0.560784f, 0.560784f, 0.737255f, 1.f);
	const Color Color::LimeGreen(0.196078f, 0.8f, 0.196078f, 1.f);
	const Color Color::Maroon(0.556863f, 0.137255f, 0.419608f, 1.f);
	const Color Color::MediumAquamarine(0.196078f, 0.8f, 0.6f, 1.f);
	const Color Color::MediumBlue(0.196078f, 0.196078f, 0.8f, 1.f);
	const Color Color::MediumForestGreen(0.419608f, 0.556863f, 0.137255f, 1.f);
	const Color Color::MediumGoldenrod(0.917647f, 0.917647f, 0.678431f, 1.f);
	const Color Color::MediumOrchid(0.576471f, 0.439216f, 0.858824f, 1.f);
	const Color Color::MediumSeaGreen(0.258824f, 0.435294f, 0.258824f, 1.f);
	const Color Color::MediumSlateBlue(0.498039f, 1.0f, 1.f);
	const Color Color::MediumSpringGreen(0.498039f, 1.0f, 1.f);
	const Color Color::MediumTurquoise(0.439216f, 0.858824f, 0.858824f, 1.f);
	const Color Color::MediumVioletRed(0.858824f, 0.439216f, 0.576471f, 1.f);
	const Color Color::MidnightBlue(0.184314f, 0.184314f, 0.309804f, 1.f);
	const Color Color::Navy(0.137255f, 0.137255f, 0.556863f, 1.f);
	const Color Color::NavyBlue(0.137255f, 0.137255f, 0.556863f, 1.f);
	const Color Color::Orange(1.f, 0.5f, 0.0f, 1.f);
	const Color Color::OrangeRed(1.0f, 0.25f, 0.0f, 1.f);
	const Color Color::Orchid(0.858824f, 0.439216f, 0.858824f, 1.f);
	const Color Color::PaleGreen(0.560784f, 0.737255f, 0.560784f, 1.f);
	const Color Color::Pink(0.737255f, 0.560784f, 0.560784f, 1.f);
	const Color Color::Plum(0.917647f, 0.678431f, 0.917647f, 1.f);
	const Color Color::Salmon(0.435294f, 0.258824f, 0.258824f, 1.f);
	const Color Color::SeaGreen(0.137255f, 0.556863f, 0.419608f, 1.f);
	const Color Color::Sienna(0.556863f, 0.419608f, 0.137255f, 1.f);
	const Color Color::SkyBlue(0.196078f, 0.6f, 0.8f, 1.f);
	const Color Color::SteelBlue(0.137255f, 0.419608f, 0.556863f, 1.f);
	const Color Color::Tan(0.858824f, 0.576471f, 0.439216f, 1.f);
	const Color Color::Thistle(0.847059f, 0.74902f, 0.847059f, 1.f);
	const Color Color::Turquoise(0.678431f, 0.917647f, 0.917647f, 1.f);
	const Color Color::Violet(0.309804f, 0.184314f, 0.309804f, 1.f);
	const Color Color::VioletRed(0.8f, 0.196078f, 0.6f, 1.f);
	const Color Color::Wheat(0.847059f, 0.847059f, 0.74902f, 1.f);
	const Color Color::YellowGreen(0.6f, 0.8f, 0.196078f, 1.f);
	const Color Color::SummerSky(0.22f, 0.69f, 0.87f, 1.f);
	const Color Color::RichBlue(0.35f, 0.35f, 0.67f, 1.f);
	const Color Color::Brass(0.71f, 0.65f, 0.26f, 1.f);
	const Color Color::Copper(0.72f, 0.45f, 0.20f, 1.f);
	const Color Color::Bronze(0.55f, 0.47f, 0.14f, 1.f);
	const Color Color::Bronze2(0.65f, 0.49f, 0.24f, 1.f);
	const Color Color::Silver(0.90f, 0.91f, 0.98f, 1.f);
	const Color Color::BrightGold(0.85f, 0.85f, 0.10f, 1.f);
	const Color Color::OldGold(0.81f, 0.71f, 0.23f, 1.f);
	const Color Color::Feldspar(0.82f, 0.57f, 0.46f, 1.f);
	const Color Color::Quartz(0.85f, 0.85f, 0.95f, 1.f);
	const Color Color::NeonPink(1.00f, 0.43f, 0.78f, 1.f);
	const Color Color::DarkPurple(0.53f, 0.12f, 0.47f, 1.f);
	const Color Color::NeonBlue(0.30f, 0.30f, 1.00f, 1.f);
	const Color Color::CoolCopper(0.85f, 0.53f, 0.10f, 1.f);
	const Color Color::MandarinOrange(0.89f, 0.47f, 0.20f, 1.f);
	const Color Color::LightWood(0.91f, 0.76f, 0.65f, 1.f);
	const Color Color::MediumWood(0.65f, 0.50f, 0.39f, 1.f);
	const Color Color::DarkWood(0.52f, 0.37f, 0.26f, 1.f);
	const Color Color::SpicyPink(1.00f, 0.11f, 0.68f, 1.f);
	const Color Color::SemiSweetChoc(0.42f, 0.26f, 0.15f, 1.f);
	const Color Color::BakersChoc(0.36f, 0.20f, 0.09f, 1.f);
	const Color Color::Flesh(0.96f, 0.80f, 0.69f, 1.f);
	const Color Color::NewTan(0.92f, 0.78f, 0.62f, 1.f);
	const Color Color::NewMidnightBlue(0.00f, 0.00f, 0.61f, 1.f);
	const Color Color::VeryDarkBrown(0.35f, 0.16f, 0.14f, 1.f);
	const Color Color::DarkBrown(0.36f, 0.25f, 0.20f, 1.f);
	const Color Color::DarkTan(0.59f, 0.41f, 0.31f, 1.f);
	const Color Color::GreenCopper(0.32f, 0.49f, 0.46f, 1.f);
	const Color Color::DkGreenCopper(0.29f, 0.46f, 0.43f, 1.f);
	const Color Color::DustyRose(0.52f, 0.39f, 0.39f, 1.f);
	const Color Color::HuntersGreen(0.13f, 0.37f, 0.31f, 1.f);
	const Color Color::Scarlet(0.55f, 0.09f, 0.09f, 1.f);

	const Color Color::Med_Purple(0.73f, 0.16f, 0.96f, 1.f);
	const Color Color::Light_Purple(0.87f, 0.58f, 0.98f, 1.f);
	const Color Color::Very_Light_Purple(0.94f, 0.81f, 0.99f, 1.f);
}