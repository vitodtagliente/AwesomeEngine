#include "renderer_inspector.h"

#include <imgui.h>
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
			// ImGui::Text("Draw Calls: %d", renderer.getStats().drawCalls);
			context.input("background", &renderer->backgroundColor);
		}
	}
}
