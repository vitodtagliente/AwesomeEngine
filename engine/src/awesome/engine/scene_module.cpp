#include "scene_module.h"

#include "world.h"
#include "object.h"
#include "component.h"
#include <awesome/core/time.h>

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
		m_world->update(delta_time);
	}
}