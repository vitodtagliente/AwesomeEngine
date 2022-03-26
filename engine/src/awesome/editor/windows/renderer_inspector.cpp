#include "renderer_inspector.h"

#include <sstream>

#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>

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
			s << "Draw Calls: " << renderer->getStats().drawCalls;
			Layout::text(s.str());
			Layout::input("background", &renderer->backgroundColor);
		}
	}

	REFLECT_EDITOR(RendererInspector)
}
