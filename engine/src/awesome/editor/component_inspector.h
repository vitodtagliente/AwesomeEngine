/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/scene/component.h>

#include "component_inspector_generated.h"

CLASS()
struct ComponentInspector : public IType
{
	ComponentInspector() = default;
	virtual ~ComponentInspector() = default;

	virtual bool canInspect(Component&) const { return false; }
	virtual void inspect(Component&) {}

	GENERATED_BODY()
};