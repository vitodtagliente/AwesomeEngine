/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cmath>

#include <imgui.h>

namespace editor
{
	class EditorColorScheme
	{
	public:
		EditorColorScheme(int backGroundColor, int textColor, int mainColor, int mainAccentColor, int highlightColor);
		void setColors(int backGroundColor, int textColor, int mainColor, int mainAccentColor, int highlightColor);
		void apply();

	private:

		// 0xRRGGBBAA
		int m_backGroundColor = 0x25213100;
		int m_textColor = 0xF4F1DE00;
		int m_mainColor = 0xDA115E00;
		int m_mainAccentColor = 0x79235900;
		int m_highlightColor = 0xC7EF0000;

		inline static int Black = 0x00000000;
		inline static int White = 0xFFFFFF00;

		inline static int AlphaTransparent = 0x00;
		inline static int Alpha20 = 0x33;
		inline static int Alpha40 = 0x66;
		inline static int Alpha50 = 0x80;
		inline static int Alpha60 = 0x99;
		inline static int Alpha80 = 0xCC;
		inline static int Alpha90 = 0xE6;
		inline static int AlphaFull = 0xFF;

		static float getR(int colorCode) { return (float)((colorCode & 0xFF000000) >> 24) / (float)(0xFF); }
		static float getG(int colorCode) { return (float)((colorCode & 0x00FF0000) >> 16) / (float)(0xFF); }
		static float getB(int colorCode) { return (float)((colorCode & 0x0000FF00) >> 8) / (float)(0xFF); }
		static float getA(int alphaCode) { return ((float)alphaCode / (float)0xFF); }

		static ImVec4 getColor(int c, int a = Alpha80) { return ImVec4(getR(c), getG(c), getB(c), getA(a)); }
		static ImVec4 darken(ImVec4 c, float p) { return ImVec4(fmax(0.f, c.x - 1.0f * p), fmax(0.f, c.y - 1.0f * p), fmax(0.f, c.z - 1.0f * p), c.w); }
		static ImVec4 lighten(ImVec4 c, float p) { return ImVec4(fmax(0.f, c.x + 1.0f * p), fmax(0.f, c.y + 1.0f * p), fmax(0.f, c.z + 1.0f * p), c.w); }

		static ImVec4 disabled(ImVec4 c) { return darken(c, 0.6f); }
		static ImVec4 hovered(ImVec4 c) { return lighten(c, 0.2f); }
		static ImVec4 active(ImVec4 c) { return lighten(ImVec4(c.x, c.y, c.z, 1.0f), 0.1f); }
		static ImVec4 collapsed(ImVec4 c) { return darken(c, 0.2f); }
	}; 
}