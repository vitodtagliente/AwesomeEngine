#include "editor_module.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <awesome/application/glfw/window_glfw.h>

namespace awesome
{
	EditorModule::EditorModule()
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
		return true;
	}
	
	void EditorModule::shutdown_implementation()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
	void EditorModule::pre_rendering_implementation()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	void EditorModule::render_implementation()
	{
		ImGui::Begin("Awesome Engine");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
	
	void EditorModule::post_rendering_implementation()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}