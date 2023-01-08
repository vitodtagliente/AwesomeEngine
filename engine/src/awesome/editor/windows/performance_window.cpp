#include "performance_window.h"

#include <string>
#include <sstream>
#include <imgui.h>

#include <awesome/application/application.h>
#include <awesome/editor/layout.h>
#include <awesome/graphics/graphics.h>
#include <awesome/ui/ui.h>

std::string PerformanceWindow::getTitle() const
{
	return "Performance";
}

void PerformanceWindow::render()
{
	// FPS
	{
		const Application::Stats& stats = Application::instance().getStats();
		std::ostringstream s;
		s << std::round(1000.0f / stats.framerate) << " ms/frame (" << stats.framerate << " FPS)";
		Layout::text(s.str());
	}

	// Renderer
	{
		std::ostringstream s;
		s << "Graphics::DrawCalls: " << Graphics::instance()->performances.drawCalls;
		Layout::text(s.str());
	}

	// UI
	{
		std::ostringstream s;
		s << "UI::DrawCalls: " << UI::instance()->performances.drawCalls;
		Layout::text(s.str());
	}
}