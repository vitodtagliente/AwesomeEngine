/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/component_inspector.h>

class Rigidbody2DComponentInspector : public ComponentInspector
{
public:
	virtual bool canInspect(Component& component) const override;
	virtual void inspect(Component& component) override;
};