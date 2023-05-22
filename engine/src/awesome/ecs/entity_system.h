/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "types.h"

#include <awesome/scene/entity.h>

#include <set>


class EntitySystem
{
public:
	std::set<StoragableEntity<Entity>> m_entities;
};
