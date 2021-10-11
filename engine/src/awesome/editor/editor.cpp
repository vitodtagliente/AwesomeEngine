#include "editor.h"

#include <typeinfo>

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "window.h"

#include "windows/entity_inspector.h"
#include "windows/performance.h"
#include "windows/renderer_inspector.h"
#include "windows/scene_inspector.h"

namespace editor
{
	Editor::Editor()
		: m_context()
		, m_windows()
	{
	}

	void Editor::startup()
	{
		addWindow<EntityInspector>();
		addWindow<Performance>();
		addWindow<RendererInspector>();
		addWindow<SceneInspector>();
	}

	void Editor::shutdown()
	{
	}

	void Editor::preRendering()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Editor::render(graphics::Renderer& renderer)
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			Window* const window = *it;
			ImGui::Begin(window->getTitle().c_str());
			// ImGui::Begin(typeid(*window).name());
			window->render(m_context);
			ImGui::End();
		}
	}

	void Editor::postRendering()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}