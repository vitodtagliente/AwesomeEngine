#include "editor_module.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <awesome/modules/glfw/application/window_glfw.h>
#include "editor.h"
#include <awesome/input/input.h>

namespace awesome
{
	EditorModule::EditorModule()
		: m_editor()
	{
	}
	
	EditorModule::~EditorModule()
	{
	}
	
	bool EditorModule::startup_implementation()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		WindowGLFW* const window = static_cast<WindowGLFW*>(Window::instance());
		ImGui_ImplGlfw_InitForOpenGL(window->getWindowHandler(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		m_editor = new Editor();
		m_editor->initialize();
		return true;
	}
	
	void EditorModule::shutdown_implementation()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorModule::update_implementation()
	{
		if (Input* const input = Input::instance())
		{
			if (input->isKeyReleased(KeyCode::F2))
				m_editor->enabled = !m_editor->enabled;
		}
	}
	
	void EditorModule::pre_rendering_implementation()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	void EditorModule::render_implementation()
	{
		if (m_editor->enabled)
		{
			m_editor->render();
		}
	}
	
	void EditorModule::post_rendering_implementation()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}