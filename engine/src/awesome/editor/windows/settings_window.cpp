#include "settings_window.h"

#include <awesome/application/application.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/layout.h>

void SettingsWindow::render()
{
	ApplicationSettings& settings = Application::instance().settings;
	Layout::input(Application::instance().settings);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		JsonFile::save(settings, std::filesystem::current_path() / ApplicationSettings::filename);
	}
}