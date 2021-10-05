#include "scene_tree_viewer.h"

#include <imgui.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

SceneTreeViewer::SceneTreeViewer()
	: m_selectedEntity()
{
}


void SceneTreeViewer::render()
{
	ImGui::Begin("SceneTree");
	World* const world = World::instance();
	for (auto it = world->getEntities().begin(); it != world->getEntities().end(); ++it)
	{
		Entity* const entity = *it;
		if (ImGui::Selectable(entity->name.c_str(), entity == m_selectedEntity))
		{
			m_selectedEntity = entity;
		}
	}
	ImGui::End();
}