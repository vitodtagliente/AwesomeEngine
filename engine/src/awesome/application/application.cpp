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
#include <awesome/scene/world.h>

#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/sprite_renderer.h>

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

	const auto& randomizeSprites = [](World& world, const float w, const float h) -> void
	{
		for (auto it = world.getEntities().begin(); it != world.getEntities().end(); ++it)
		{
			Entity* const entity = *it;
			entity->transform.position = math::vec3(math::random(-w, w), math::random(-h, h), 0.0f);
			entity->transform.rotation.z = math::random(0.f, 360.f);
			entity->transform.scale = math::vec3(math::random(0.7f, 1.4f), math::random(0.7f, 1.4f), 1.f);
		}
	};

	for (int i = 0; i < 500; ++i)
	{
		const float spriteSize = 1.0f / 11;
		{
			Entity* const entity = m_world.spawn(math::vec3::zero, math::quaternion());
			entity->name = std::string("entity") + std::to_string(i + 1);
			if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
			{
				component->texture = library.get("sheet");
				component->rect = TextureRect(spriteSize * 9, spriteSize * math::random(4, 10), spriteSize, spriteSize);
			}
			if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
			{
				component->type = GizmosRenderer::Type::Rect;
			}
		}
	}

	const float generateTime = .2f;
	float timer = generateTime;

	while (m_canvas.isOpen())
	{
		m_canvas.update();
		m_time.tick();
		update();
		context.viewport(m_canvas.width(), m_canvas.height());
		// pixel perfect
		const float w = m_canvas.width() / 2 / 32;
		const float h = m_canvas.height() / 2 / 32;
		{			
			context.camera = math::mat4::orthographic(-w, w, -h, h, -30, 1000);
		}

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

		timer -= m_time.getDeltaTime();
		if (timer <= 0.0f)
		{
			randomizeSprites(m_world, w, h);
			timer = generateTime;
		}

		context.test();

		if (m_input.isKeyPressed(KeyCode::A))
		{
			Entity* const entity = m_world.spawn(math::vec3::zero, {});
			entity->name = "entity-" + std::to_string(++id);
		}
		m_input.update();
		m_world.update(m_time.getDeltaTime());
		m_world.render(renderer);

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
