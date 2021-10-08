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
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

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

	TextureLibrary library;
	library.add("sheet", "../assets/spritesheet.png");
	context.testTexture = library.get("sheet");

	std::vector<std::pair<math::transform, int>> sprites;
	const auto& generateSprites = [&sprites]() -> void
	{
		sprites.clear();
		for (int i = 0; i < 100; ++i)
		{
			math::transform t;
			t.scale = math::vec3(math::random(0.1f, 0.25f));
			t.position = math::vec3(math::random(-.8f, .8f), math::random(-.8f, .8f), 0.0f);
			t.rotation.z = math::random(0.f, 360.f);
			t.update();

			sprites.push_back(std::make_pair(t, math::random(4, 10)));
		}
	};
	const float generateTime = 10.0f;
	float timer = generateTime;

	while (m_canvas.isOpen())
	{
		m_canvas.update();
		m_time.tick();
		update();
		context.viewport(m_canvas.width(), m_canvas.height());

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

		const float size = 1.0f / 11;
		for (int i = 0; i < sprites.size(); ++i)
		{
			const auto& pair = sprites[i];
			renderer.drawSprite(library.get("sheet"), pair.first.matrix(), TextureRect(size * 9, size * pair.second, size, size));
		}

		timer -= m_time.getDeltaTime();
		if (timer <= 0.0f)
		{
			generateSprites();
			timer = generateTime;
		}

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
