/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/component_inspector.h>

class AudioSourceComponentInspector : public ComponentInspector
{
public:
	virtual bool canInspect(Component& component) const override;
	virtual void inspect(Component& component) override;
};