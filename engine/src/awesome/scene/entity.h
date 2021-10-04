/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>
#include <awesome/core/string_id.h>
#include <vdtmath/transform.h>

#include "component.h"

class World;

class Entity
{
public:

	std::string name;
	std::string tag;
	math::transform transform;

	void prepareToSpawn(World& world);
	void prepareToDestroy();


private:

	string_id m_id;
	Entity* m_parent;
	std::vector<Entity*> m_children;
	std::vector<Component*> m_components;
};