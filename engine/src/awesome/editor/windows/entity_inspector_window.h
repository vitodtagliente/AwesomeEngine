/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "entity_inspector_window_generated.h"

CLASS(Type = Window)
class EntityInspectorWindow : public Window
{
public:
	EntityInspectorWindow() = default;

	virtual std::string getTitle() const override;
	virtual void render() override;

	GENERATED_BODY()
};