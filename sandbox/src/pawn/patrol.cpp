#include "patrol.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>

void Patrol::update(double deltaTime)
{
	
}

void Patrol::inspect()
{
	Component::inspect();
}

json::value Patrol::serialize() const
{
	json::value data = Component::serialize();

	return data;
}

void Patrol::deserialize(const json::value& data)
{
	Component::deserialize(data);
}

REFLECT_COMPONENT(Patrol)