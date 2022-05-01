/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

namespace editor
{
	class SettingsWindow : public Window
	{
	public:
		SettingsWindow() = default;

		std::string getTitle() const override { return "Settings"; }
		void render() override;

		REFLECT()
	};
}