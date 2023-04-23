/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/scene/entity.h>

#include "scene_generated.h"

CLASS()
struct Scene : public IType
{
	PROPERTY() std::vector<Entity> entities;

	GENERATED_BODY()
};