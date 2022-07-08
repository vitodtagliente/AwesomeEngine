#include "transform_system.h"

void TransformSystem::update(const double deltaTime)
{
	for (Component& component : components())
	{
		component.data.update();
	}
}

REFLECT_SYSTEM(TransformSystem)
