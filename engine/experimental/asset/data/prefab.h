/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/scene/entity.h>

#include "prefab_generated.h"

CLASS()
struct Prefab : public IType
{
	PROPERTY() Entity entity;

	GENERATED_BODY()
};