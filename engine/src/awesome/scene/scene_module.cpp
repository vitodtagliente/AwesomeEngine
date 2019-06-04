#include "scene_module.h"

#include "world.h"
#include "object.h"
#include "component.h"
#include "../application/time.h"
#include "../graphics/components/rendering_component.h"
#include "..//graphics/renderer.h"

namespace awesome
{
	SceneModule::SceneModule()
		: m_world()
	{
	}

	SceneModule::~SceneModule()
	{
	}

	bool SceneModule::startup_implementation()
	{
		m_world = new World();
		return true;
	}

	void SceneModule::shutdown_implementation()
	{
		m_world->clear();
	}

	void SceneModule::update_implementation()
	{
		const double delta_time = Time::instance()->getDeltaTime();
		for (Object* const object : m_world->getObjects())
		{
			object->update(delta_time);
		}
	}

	void SceneModule::pre_rendering_implementation()
	{
	}

	void SceneModule::render_implementation()
	{
		Renderer* const renderer = Renderer::instance();
		for (Object* const object : m_world->getObjects())
		{
			for (RenderingComponent* rendering_component : object->getComponents<RenderingComponent>())
			{
				rendering_component->push_data(renderer);
			}
		}
	}

	void SceneModule::post_rendering_implementation()
	{
	}
}