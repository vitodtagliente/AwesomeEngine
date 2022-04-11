#include "renderer_window.h"

#include <sstream>

#include <awesome/editor/layout.h>

namespace editor
{
	void RendererWindow::render()
	{
		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
			std::ostringstream s;
			s << "Draw Calls: " << m_stats.drawCalls;
			Layout::text(s.str());
			Layout::input("background", renderer->backgroundColor);
		}
	}

	void RendererWindow::update(const double)
	{
		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
			m_stats = renderer->getStats();
		}
	}

	REFLECT_EDITOR(RendererWindow)
}
