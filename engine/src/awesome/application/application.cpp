#include <glad/glad.h>
#include "application.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/graphics/color.h>
#include <awesome/graphics/context.h>

#include <awesome/editor/scene_tree_viewer.h>

Application::Application()
{
}

Application::~Application()
{
}

int Application::run()
{
	m_canvas.init();
	m_canvas.open();

	gladLoadGL();

	Context context;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplGlfw_InitForOpenGL(m_canvas.getHandler(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	SceneTreeViewer sceneTree;
	sceneTree.init(&m_world);

	while (m_canvas.isOpen())
	{
		m_canvas.update();
		update();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		render();
		context.clear(Color::Yellow);

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::Begin("Performance Viewer");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		sceneTree.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

void Application::update()
{
	
}

void Application::render()
{
}
