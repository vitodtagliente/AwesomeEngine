#include "performance.h"

#include <string>
#include <sstream>
#include <imgui.h>

#include "../context.h"

namespace editor
{
	Performance::Performance()
		: Window()
	{
	}

	std::string Performance::getTitle() const
	{
		return "Performance";
	}

	void Performance::render(Context& context)
	{
		std::ostringstream s;
		s << 1000.0f / ImGui::GetIO().Framerate << " ms/frame (" << ImGui::GetIO().Framerate << " FPS)";
		context.text(s.str());
	}
}