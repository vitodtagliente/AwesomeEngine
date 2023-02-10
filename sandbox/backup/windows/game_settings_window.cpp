#include "game_settings_window.h"

#include <awesome/editor/layout.h>

#include "../data/game_settings.h"

void GameSettingsWindow::render()
{
	GameSettings& settings = GameSettings::instance();
	Layout::input(settings);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		settings.save();
	}
}