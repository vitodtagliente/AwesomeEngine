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