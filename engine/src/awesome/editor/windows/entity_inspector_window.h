/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

class EntityInspectorWindow : public Window
{
public:
	EntityInspectorWindow() = default;

	virtual char* const getTitle() const override;
	virtual void render() override;
};