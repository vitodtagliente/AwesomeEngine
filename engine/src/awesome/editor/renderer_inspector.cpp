#include "renderer_inspector.h"

#include <imgui.h>
#include <awesome/graphics/renderer.h>

RendererInspector::RendererInspector()
{
}

void RendererInspector::render(graphics::Renderer& renderer)
{
	ImGui::Begin("Renderer Inspector");
	ImGui::Text("Draw Calls: %d", renderer.getStats().drawCalls);
	ImGui::ColorEdit4("background", renderer.backgroundColor.data);
	ImGui::End();
}
