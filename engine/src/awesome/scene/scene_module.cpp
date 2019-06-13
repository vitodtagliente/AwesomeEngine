#include "scene_module.h"

#include "world.h"
#include "object.h"
#include "component.h"
#include <awesome/application/time.h>

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
			if (object->getState() == Object::State::Normal)
			{
				object->update(delta_time);
			}
			else if (object->getState() == Object::State::PendingDestroy)
			{
				// #todo
			}
		}
	}
}