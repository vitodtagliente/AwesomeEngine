#include "performance_window.h"

#include <string>
#include <sstream>

#include <awesome/editor/widgets/form_layout.h>
#include <awesome/engine/engine.h>
#include <awesome/graphics/graphics.h>

char* const PerformanceWindow::getTitle() const
{
	return "Performance";
}

void PerformanceWindow::render()
{
	// FPS
	{
		const Engine::Stats& stats = Engine::instance().getStats();
		std::ostringstream s;
		s << std::round(1000.0f / stats.framerate) << " ms/frame (" << stats.framerate << " FPS)";
		FormLayout::text(s.str().c_str());
	}

	// Renderer
	{
		std::ostringstream s;
		s << "Graphics::DrawCalls: " << Graphics::instance()->performances.drawCalls;
		FormLayout::text(s.str().c_str());
	}
}