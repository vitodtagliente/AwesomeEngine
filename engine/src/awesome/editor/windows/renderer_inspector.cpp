#include "renderer_inspector.h"

#include <sstream>
#include <awesome/graphics/renderer.h>

#include "../context.h"

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

	void RendererInspector::render(Context& context)
	{
		if (graphics::Renderer* const renderer = graphics::Renderer::instance())
		{
			std::ostringstream s;
			s << "Draw Calls: " << renderer->getStats().drawCalls;
			context.text(s.str());
			context.input("background", &renderer->backgroundColor);
		}
	}
}
