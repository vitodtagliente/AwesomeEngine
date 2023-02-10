/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/entity.h>

#include "control_generated.h"

CLASS(Type = Entity)
class Control : public Entity
{
public:
	Control() = default;
	virtual ~Control() = default;

	GENERATED_BODY()
};