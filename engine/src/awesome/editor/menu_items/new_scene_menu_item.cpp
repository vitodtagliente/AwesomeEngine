#include "new_scene_menu_item.h"

#include <awesome/entity/world.h>

namespace editor
{
	void NewSceneMenuItem::execute()
	{
		World::instance().clear();
	}

	REFLECT_MENU_ITEM(NewSceneMenuItem)
}