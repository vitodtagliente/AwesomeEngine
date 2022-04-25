#include "performance_window.h"

#include <string>
#include <sstream>
#include <imgui.h>

#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

namespace editor
{
	void PerformanceWindow::render()
	{
		// FPS
		{
			std::ostringstream s;
			s << std::round(1000.0f / ImGui::GetIO().Framerate) << " ms/frame (" << std::round(ImGui::GetIO().Framerate) << " FPS)";
			Layout::text(s.str());
		}

		// Scene loading
		{
			std::ostringstream s;
			s << "World: ";

			World& world = World::instance();
			size_t progress = 0;
			if (world.isLoading(progress))
			{
				s << "loading... " << progress << "%";
			}
			else
			{
				s << "loaded";
			}

			Layout::text(s.str());
		}
	}

	REFLECT_WINDOW(PerformanceWindow)
}