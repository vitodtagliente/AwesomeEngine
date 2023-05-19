/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "types.h"
#include <set>


class EntitySystem
{
public:
	std::set<EntityStorageId> m_entities;
};
