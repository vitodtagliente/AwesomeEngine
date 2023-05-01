/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

class PerformanceWindow : public Window
{
public:
	PerformanceWindow() = default;

	virtual char* const getTitle() const override;
	virtual void render() override;
};