#include "ui_module.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "../application/glfw/window_glfw.h"

namespace awesome
{
	UIModule::UIModule()
	{
	}

	UIModule::~UIModule()
	{
	}

	bool UIModule::startup_implementation()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		WindowGLFW* const window = static_cast<WindowGLFW*>(Window::instance());
		ImGui_ImplGlfw_InitForOpenGL(window->getWindowHandler(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
		return true;
	}

	void UIModule::shutdown_implementation()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UIModule::pre_rendering_implementation()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UIModule::render_implementation()
	{
		ImGui::Begin("Hello, world!");
		ImGui::Text("This is some useful text.");
		ImGui::End();
	}

	void UIModule::post_rendering_implementation()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}