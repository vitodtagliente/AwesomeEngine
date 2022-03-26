#include "color_scheme.h"

namespace editor
{
	ColorScheme::ColorScheme(int backGroundColor, int textColor, int mainColor, int mainAccentColor, int highlightColor)
		: m_backGroundColor(backGroundColor)
		, m_textColor(textColor)
		, m_mainColor(mainColor)
		, m_mainAccentColor(mainAccentColor)
		, m_highlightColor(highlightColor)
	{
	}

	void ColorScheme::setColors(int backGroundColor, int textColor, int mainColor, int mainAccentColor, int highlightColor)
	{
		backGroundColor = backGroundColor;
		m_textColor = textColor;
		m_mainColor = mainColor;
		m_mainAccentColor = mainAccentColor;
		m_highlightColor = highlightColor;
	}

	void ColorScheme::apply()
	{
		test();
		if (true) return;

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.FrameRounding = 0.0f;
		style.ScrollbarRounding = 0;

		ImVec4* colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_Text] = getColor(m_textColor);
		colors[ImGuiCol_TextDisabled] = disabled(colors[ImGuiCol_Text]);
		colors[ImGuiCol_WindowBg] = getColor(m_backGroundColor);
		colors[ImGuiCol_ChildBg] = getColor(Black, Alpha20);
		colors[ImGuiCol_PopupBg] = getColor(m_backGroundColor, Alpha90);
		colors[ImGuiCol_Border] = lighten(getColor(m_backGroundColor), 0.4f);
		colors[ImGuiCol_BorderShadow] = getColor(Black);
		colors[ImGuiCol_FrameBg] = getColor(m_mainAccentColor, Alpha40);
		colors[ImGuiCol_FrameBgHovered] = hovered(colors[ImGuiCol_FrameBg]);
		colors[ImGuiCol_FrameBgActive] = active(colors[ImGuiCol_FrameBg]);
		colors[ImGuiCol_TitleBg] = getColor(m_backGroundColor, Alpha80);
		colors[ImGuiCol_TitleBgActive] = active(colors[ImGuiCol_TitleBg]);
		colors[ImGuiCol_TitleBgCollapsed] = collapsed(colors[ImGuiCol_TitleBg]);
		colors[ImGuiCol_MenuBarBg] = darken(getColor(m_backGroundColor), 0.2f);
		colors[ImGuiCol_ScrollbarBg] = lighten(getColor(m_backGroundColor, Alpha50), 0.4f);
		colors[ImGuiCol_ScrollbarGrab] = lighten(getColor(m_backGroundColor), 0.3f);
		colors[ImGuiCol_ScrollbarGrabHovered] = hovered(colors[ImGuiCol_ScrollbarGrab]);
		colors[ImGuiCol_ScrollbarGrabActive] = active(colors[ImGuiCol_ScrollbarGrab]);
		colors[ImGuiCol_CheckMark] = getColor(m_highlightColor);
		colors[ImGuiCol_SliderGrab] = getColor(m_highlightColor);
		colors[ImGuiCol_SliderGrabActive] = active(colors[ImGuiCol_SliderGrab]);
		colors[ImGuiCol_Button] = getColor(m_mainColor, Alpha80);
		colors[ImGuiCol_ButtonHovered] = hovered(colors[ImGuiCol_Button]);
		colors[ImGuiCol_ButtonActive] = active(colors[ImGuiCol_Button]);
		colors[ImGuiCol_Header] = getColor(m_mainAccentColor, Alpha80);
		colors[ImGuiCol_HeaderHovered] = hovered(colors[ImGuiCol_Header]);
		colors[ImGuiCol_HeaderActive] = active(colors[ImGuiCol_Header]);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = hovered(colors[ImGuiCol_Separator]);
		colors[ImGuiCol_SeparatorActive] = active(colors[ImGuiCol_Separator]);
		colors[ImGuiCol_ResizeGrip] = getColor(m_mainColor, Alpha20);
		colors[ImGuiCol_ResizeGripHovered] = hovered(colors[ImGuiCol_ResizeGrip]);
		colors[ImGuiCol_ResizeGripActive] = active(colors[ImGuiCol_ResizeGrip]);
		colors[ImGuiCol_Tab] = getColor(m_mainColor, Alpha60);
		colors[ImGuiCol_TabHovered] = hovered(colors[ImGuiCol_Tab]);
		colors[ImGuiCol_TabActive] = active(colors[ImGuiCol_Tab]);
		colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
		colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive];
		colors[ImGuiCol_DockingPreview] = darken(colors[ImGuiCol_HeaderActive], 0.2f);
		colors[ImGuiCol_DockingEmptyBg] = darken(colors[ImGuiCol_HeaderActive], 0.6f);
		colors[ImGuiCol_PlotLines] = getColor(m_highlightColor);
		colors[ImGuiCol_PlotLinesHovered] = hovered(colors[ImGuiCol_PlotLines]);
		colors[ImGuiCol_PlotHistogram] = getColor(m_highlightColor);
		colors[ImGuiCol_PlotHistogramHovered] = hovered(colors[ImGuiCol_PlotHistogram]);
		colors[ImGuiCol_TextSelectedBg] = getColor(m_highlightColor, Alpha40);
		colors[ImGuiCol_DragDropTarget] = getColor(m_highlightColor, Alpha80);;
		colors[ImGuiCol_NavHighlight] = getColor(White);
		colors[ImGuiCol_NavWindowingHighlight] = getColor(White, Alpha80);
		colors[ImGuiCol_NavWindowingDimBg] = getColor(White, Alpha20);
		colors[ImGuiCol_ModalWindowDimBg] = getColor(Black, Alpha60);

		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_Right;
	}

	void ColorScheme::test()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameRounding = 0.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.0f;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}
}