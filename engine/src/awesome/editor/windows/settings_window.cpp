#include "settings_window.h"

#include <awesome/application/application.h>
#include <awesome/editor/layout.h>

namespace editor
{
	void SettingsWindow::render()
	{
		auto& settings = Application::instance().settings;
		Layout::input("FPS", settings.fps);
		Layout::input("Mode", settings.mode);
	}

	REFLECT_WINDOW(SettingsWindow)
}