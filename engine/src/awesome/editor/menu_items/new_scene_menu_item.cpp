#include "new_scene_menu_item.h"

#include <awesome/editor/state.h>
#include <awesome/entity/world.h>

namespace editor
{
	void NewSceneMenuItem::execute()
	{
		State::instance().select();
		World::instance().clear();
	}
}