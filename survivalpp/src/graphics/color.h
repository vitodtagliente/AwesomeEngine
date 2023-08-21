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

		static Color random();
		static Color random(const Color& color1, const Color& color2);

		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;
		static const Color White;
		static const Color Black;
		static const Color Transparent;

		static const Color Gray05;
		static const Color Gray10;
		static const Color Gray15;
		static const Color Gray20;
		static const Color Gray25;
		static const Color Gray30;
		static const Color Gray35;
		static const Color Gray40;
		static const Color Gray45;
		static const Color Gray50;
		static const Color Gray55;
		static const Color Gray60;
		static const Color Gray65;
		static const Color Gray70;
		static const Color Gray75;
		static const Color Gray80;
		static const Color Gray85;
		static const Color Gray90;
		static const Color Gray95;

		static const Color DimGray;
		static const Color Gray;
		static const Color LightGray;
		static const Color VLightGray;

		static const Color Aquamarine;
		static const Color BlueViolet;
		static const Color Brown;
		static const Color CadetBlue;
		static const Color Coral;
		static const Color CornflowerBlue;
		static const Color DarkGreen;
		static const Color DarkOliveGreen;
		static const Color DarkOrchid;
		static const Color DarkSlateBlue;
		static const Color DarkSlateGray;
		static const Color DarkTurquoise;
		static const Color Firebrick;
		static const Color ForestGreen;
		static const Color Gold;
		static const Color Goldenrod;
		static const Color GreenYellow;
		static const Color IndianRed;
		static const Color Khaki;
		static const Color LightBlue;
		static const Color LightSteelBlue;
		static const Color LimeGreen;
		static const Color Maroon;
		static const Color MediumAquamarine;
		static const Color MediumBlue;
		static const Color MediumForestGreen;
		static const Color MediumGoldenrod;
		static const Color MediumOrchid;
		static const Color MediumSeaGreen;
		static const Color MediumSlateBlue;
		static const Color MediumSpringGreen;
		static const Color MediumTurquoise;
		static const Color MediumVioletRed;
		static const Color MidnightBlue;
		static const Color Navy;
		static const Color NavyBlue;
		static const Color Orange;
		static const Color OrangeRed;
		static const Color Orchid;
		static const Color PaleGreen;
		static const Color Pink;
		static const Color Plum;
		static const Color Salmon;
		static const Color SeaGreen;
		static const Color Sienna;
		static const Color SkyBlue;
		static const Color SteelBlue;
		static const Color Tan;
		static const Color Thistle;
		static const Color Turquoise;
		static const Color Violet;
		static const Color VioletRed;
		static const Color Wheat;
		static const Color YellowGreen;
		static const Color SummerSky;
		static const Color RichBlue;
		static const Color Brass;
		static const Color Copper;
		static const Color Bronze;
		static const Color Bronze2;
		static const Color Silver;
		static const Color BrightGold;
		static const Color OldGold;
		static const Color Feldspar;
		static const Color Quartz;
		static const Color NeonPink;
		static const Color DarkPurple;
		static const Color NeonBlue;
		static const Color CoolCopper;
		static const Color MandarinOrange;
		static const Color LightWood;
		static const Color MediumWood;
		static const Color DarkWood;
		static const Color SpicyPink;
		static const Color SemiSweetChoc;
		static const Color BakersChoc;
		static const Color Flesh;
		static const Color NewTan;
		static const Color NewMidnightBlue;
		static const Color VeryDarkBrown;
		static const Color DarkBrown;
		static const Color DarkTan;
		static const Color GreenCopper;
		static const Color DkGreenCopper;
		static const Color DustyRose;
		static const Color HuntersGreen;
		static const Color Scarlet;

		static const Color Med_Purple;
		static const Color Light_Purple;
		static const Color Very_Light_Purple;
	};
}