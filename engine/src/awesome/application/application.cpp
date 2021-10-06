#include <iostream>
#include <glad/glad.h>
#include "application.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/graphics/color.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>

#include <awesome/editor/entity_inspector.h>
#include <awesome/editor/renderer_inspector.h>
#include <awesome/editor/scene_tree_viewer.h>

#include <vdtmath/math.h>
#include <awesome/scene/entity.h>

Application::Application()
{
}

Application::~Application()
{
}

int Application::run()
{
	static int id = 0;

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

	EntityInspector inspector;
	SceneTreeViewer sceneTree;
	RendererInspector rendererInspector;

	Renderer renderer(context);

	while (m_canvas.isOpen())
	{
		m_canvas.update();
		update();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		render();
		renderer.begin();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::Begin("Performance Viewer");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		inspector.render(sceneTree.getSelectedEntity());
		sceneTree.render();
		rendererInspector.render(renderer);

		renderer.getGizmos().rect(math::vec3::zero, 0.5f, 0.5f, Color::Red);
		renderer.getGizmos().circle(math::vec3::zero, 1.0f, Color::Yellow);
		context.test();

		if (m_input.isKeyPressed(KeyCode::A))
		{
			Entity* const entity = m_world.spawn(math::vec3::zero, {});
			entity->name = "entity-" + std::to_string(++id);
		}
		m_input.update();

		renderer.flush();

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
