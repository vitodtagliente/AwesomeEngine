#include "scene_tree_viewer.h"

#include <imgui.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

SceneTreeViewer::SceneTreeViewer()
	: m_world()
{
}

void SceneTreeViewer::init(World* const world)
{
	m_world = world;
}

void SceneTreeViewer::render()
{
	ImGui::Begin("SceneTree");
	for (auto it = m_world->getEntities().begin(); it != m_world->getEntities().end(); ++it)
	{
		Entity* const entity = *it;
		ImGui::TreeNode(entity->name.c_str());
	}
	ImGui::End();
}