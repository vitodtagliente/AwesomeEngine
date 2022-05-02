#include "show_windows_menu_item.h"

#include <awesome/editor/state.h>

namespace editor
{
	std::string ShowWindowsMenuItem::getName() const
	{
		return State::instance().showWindows ? "Hide windows" : "Show windows";
	}

	void ShowWindowsMenuItem::execute()
	{
		State::instance().showWindows = !State::instance().showWindows;
	}

	REFLECT_MENU_ITEM(ShowWindowsMenuItem)
}