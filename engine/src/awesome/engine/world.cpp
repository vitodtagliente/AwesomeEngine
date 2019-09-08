#include "world.h"

#include "object.h"

namespace awesome
{
	World::World()
		: m_objects()
	{
	}
	
	World::~World()
	{
	}

	void World::update(const double t_deltaTime)
	{
		for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			Object* const object = *it;
			if (object->getState() == Object::State::Normal)
			{
				object->update(t_deltaTime);
			}
			else if (object->getState() == Object::State::PendingDestroy)
			{
				m_objects.erase(it);
				delete object;
			}
		}
	}

	void World::clear()
	{
		for (Object* const object : m_objects)
		{
			if (object != nullptr)
			{
				object->destroy();
				delete object;
			}
		}
	}
}