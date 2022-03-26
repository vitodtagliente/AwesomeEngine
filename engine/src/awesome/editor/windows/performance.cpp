#include "performance.h"

#include <string>
#include <sstream>
#include <imgui.h>

#include <awesome/editor/layout.h>

namespace editor
{
	Performance::Performance()
		: Window()
	{
	}

	void Performance::render()
	{
		std::ostringstream s;
		s << std::round(1000.0f / ImGui::GetIO().Framerate) << " ms/frame (" << std::round(ImGui::GetIO().Framerate) << " FPS)";
		Layout::text(s.str());
	}

	REFLECT_EDITOR(Performance)
}