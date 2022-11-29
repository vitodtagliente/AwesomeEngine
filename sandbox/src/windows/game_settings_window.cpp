#include "game_settings_window.h"

#include <awesome/editor/layout.h>

#include "../data/game_settings.h"

void GameSettingsWindow::render()
{
	GameSettings& settings = GameSettings::instance();
	Layout::input<WeaponItem>("Weapons", settings.weapons, [](WeaponItem& weapon) -> void
		{
			Layout::input(weapon);
			Layout::input<WeaponLevel>("Levels", weapon.levels, [](WeaponLevel& level) -> void
				{
					Layout::input(level);
				}
			);
		}
	);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		settings.save();
	}
}