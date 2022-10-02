/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "performance_window_generated.h"

CLASS()
class PerformanceWindow : public Window
{
public:
	PerformanceWindow() = default;

	std::string getTitle() const override { return "Performance"; }
	void render() override;

	GENERATED_BODY()
};