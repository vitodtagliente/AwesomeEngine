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

#include <vdtmath/math.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
#include <awesome/components/sprite_renderer.h>

#include <awesome/editor/editor.h>

using namespace graphics;

Application::Application(const std::initializer_list<Module*> modules)
	: m_modules()
{
	for (auto it = modules.begin(); it != modules.end(); ++it)
	{
		m_modules.push_back(*it);
		(*it)->startup();
	}
}

Application::~Application()
{
}

int Application::run()
{
	static int id = 0;

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

	World m_world;

	graphics::Renderer renderer(context);

	TextureLibrary library;
	library.add("sheet", "../assets/spritesheet.png");
	context.testTexture = library.get("sheet");

	const auto& randomizeSprites = [](World& world, const float w, const float h) -> void
	{
		for (auto it = world.getEntities().begin(); it != world.getEntities().end(); ++it)
		{
			Entity* const entity = *it;
			if (entity->transform.isStatic) continue;
			if (entity->tag != "sprite") continue;

			entity->transform.position = math::vec3(math::random(-w, w), math::random(-h, h), 0.0f);
			entity->transform.rotation.z = math::random(0.f, 360.f);
			entity->transform.scale = math::vec3(math::random(0.7f, 1.4f), math::random(0.7f, 1.4f), 1.f);
		}
	};


	// camera setup
	{
		Entity* const entity = m_world.spawn(math::vec3::zero, math::quaternion::identity);
		entity->name = std::string("camera");
		entity->tag = "camera";
		entity->addComponent<OrthographicCamera>();
		entity->addComponent<CameraController2d>();
	}

	// sprites setup
	for (int i = 0; i < 100; ++i)
	{
		const float spriteSize = 1.0f / 11;
		{
			Entity* const entity = m_world.spawn(math::vec3::zero, math::quaternion::identity);
			entity->name = std::string("entity") + std::to_string(i + 1);
			entity->tag = "sprite";
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

	const float generateTime = 1.f;
	float timer = generateTime;

	init();

	while (m_canvas.isOpen())
	{
		m_canvas.update();
		m_time.tick();
		update();
		const float w = m_canvas.getWidth() / 2 / 32;
		const float h = m_canvas.getHeight() / 2 / 32;

		if (m_input.isKeyPressed(KeyCode::A))
		{
			Entity* const entity = m_world.spawn(math::vec3::zero, {});
			entity->name = "entity-" + std::to_string(++id);
		}
		m_input.update();
		m_world.update(m_time.getDeltaTime());

		timer -= m_time.getDeltaTime();
		if (timer <= 0.0f)
		{
			randomizeSprites(m_world, w, h);
			timer = generateTime;
		}

		renderer.begin();
		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			Module* const module = *it;
			module->preRendering();
		}
		
		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			Module* const module = *it;
			module->render(renderer);
		}
		m_world.render(renderer);

		renderer.flush();

		for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
		{
			Module* const module = *it;
			module->postRendering();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

void Application::init()
{
	addModule<editor::Editor>();
}

void Application::update()
{

}

void Application::render()
{
}
