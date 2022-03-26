#include "renderer_inspector.h"

#include <sstream>

#include <awesome/editor/layout.h>

namespace editor
{
	RendererInspector::RendererInspector()
		: Window()
	{
	}

	std::string RendererInspector::getTitle() const
	{
		return "Renderer";
	}

	void RendererInspector::render()
	{
		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
			std::ostringstream s;
			s << "Draw Calls: " << m_stats.drawCalls;
			Layout::text(s.str());
			Layout::input("background", &renderer->backgroundColor);
		}
	}

	void RendererInspector::update(const double deltaTime)
	{
		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
			m_stats = renderer->getStats();
		}
	}

	REFLECT_EDITOR(RendererInspector)
}
