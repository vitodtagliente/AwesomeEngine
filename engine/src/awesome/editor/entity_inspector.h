/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "panel.h"

class Entity;

class EntityInspector
{
public:
	EntityInspector();

	void render(Entity* const entity);

};