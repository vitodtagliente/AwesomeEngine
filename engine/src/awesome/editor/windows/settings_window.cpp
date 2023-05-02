#include "settings_window.h"

#include <awesome/data/type_file.h>
#include <awesome/editor/text_icon.h>
#include <awesome/editor/widgets/form_layout.h>
#include <awesome/editor/widgets/type_layout.h>
#include <awesome/engine/engine.h>

char* const SettingsWindow::getTitle() const
{
	return "Settings";
}

void SettingsWindow::render()
{
	EngineSettings& settings = Engine::instance().settings;
	TypeLayout::input(settings);

	FormLayout::separator();

	if (FormLayout::button(TextIcon::save(" Save").c_str()))
	{
		TypeFile::save(settings, std::filesystem::current_path() / EngineSettings::filename);
	}
}