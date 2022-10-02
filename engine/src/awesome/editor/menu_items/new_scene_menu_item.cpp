#include "new_scene_menu_item.h"

#include <awesome/editor/state.h>
#include <awesome/entity/world.h>

void NewSceneMenuItem::execute()
{
	State::instance().select();
	World::instance().clear();
}