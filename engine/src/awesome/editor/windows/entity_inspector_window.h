/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "entity_inspector_window_generated.h"

CLASS(Category = Window)
class EntityInspectorWindow : public Window
{
public:
	EntityInspectorWindow() = default;

	std::string getTitle() const override { return "Entity Inspector"; }
	void render() override;

	GENERATED_BODY()
};