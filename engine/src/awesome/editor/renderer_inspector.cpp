#include "renderer_inspector.h"

#include <imgui.h>
#include <awesome/graphics/renderer.h>

RendererInspector::RendererInspector()
{
}

void RendererInspector::render(Renderer& renderer)
{
	ImGui::Begin("Renderer Inspector");
	ImGui::ColorEdit4("background", renderer.backgroundColor.data);
	ImGui::End();
}
