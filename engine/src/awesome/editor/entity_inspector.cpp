#include "entity_inspector.h"

#include <imgui.h>
#include <awesome/scene/entity.h>

EntityInspector::EntityInspector()
{
}


void EntityInspector::render(Entity* const entity)
{
	ImGui::Begin("Entity Inspector");
	if (entity)
	{
		ImGui::InputFloat3("position", entity->transform.position.data);
		ImGui::InputFloat3("rotation", entity->transform.rotation.data);
		ImGui::InputFloat3("scale", entity->transform.scale.data);
	}
	ImGui::End();
}