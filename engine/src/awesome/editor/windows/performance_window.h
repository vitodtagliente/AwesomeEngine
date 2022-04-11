/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

namespace editor
{
	class PerformanceWindow : public Window
	{
	public:
		PerformanceWindow() = default;

		std::string getTitle() const override { return "Performance"; }
		void render() override;

		REFLECT()
	};
}