/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/application/application.h>
#include <awesome/editor/window.h>

namespace editor
{
	class SettingsWindow : public Window
	{
	public:
		SettingsWindow();

		std::string getTitle() const override { return "Settings"; }
		void render() override;

		REFLECT()

	private:
		Application::Settings m_settings;
	};
}