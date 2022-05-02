#include "settings_window.h"

#include <awesome/application/application.h>
#include <awesome/editor/layout.h>

namespace editor
{
	SettingsWindow::SettingsWindow()
		: m_settings(Application::instance().getSettings())
	{
	}

	void SettingsWindow::render()
	{
		Layout::input("FPS", m_settings.fps);
		Layout::input("Mode", m_settings.mode);
		std::string path = m_settings.workspacePath.string();
		Layout::input("Path", path);
		if (path != m_settings.workspacePath.string())
		{
			m_settings.workspacePath = path;
		}

		if (Layout::button(TextIcon::save(" Save")))
		{
			m_settings.save(std::filesystem::current_path() / "settings.json");
		}
	}

	REFLECT_WINDOW(SettingsWindow)
}