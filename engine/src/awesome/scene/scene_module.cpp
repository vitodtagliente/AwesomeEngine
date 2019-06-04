#include "scene_module.h"

#include "world.h"
#include "object.h"
#include "component.h"
#include "../application/time.h"

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
	}

	void SceneModule::post_rendering_implementation()
	{
	}
}