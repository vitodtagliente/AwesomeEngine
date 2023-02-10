/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "performance_window_generated.h"

CLASS(Type = Window)
class PerformanceWindow : public Window
{
public:
	PerformanceWindow() = default;

	virtual std::string getTitle() const override;
	virtual void render() override;

	GENERATED_BODY()
};