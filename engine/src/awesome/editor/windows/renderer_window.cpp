#include "renderer_window.h"

#include <sstream>

#include <awesome/editor/layout.h>

namespace editor
{
	void RendererWindow::render()
	{
		std::ostringstream s;
		// s << "Draw Calls: " << m_stats.drawCalls;
		Layout::text(s.str());
	}

	void RendererWindow::update(const double)
	{
		// m_stats = graphics::Renderer::instance().getStats();
	}

	REFLECT_WINDOW(RendererWindow)
}
