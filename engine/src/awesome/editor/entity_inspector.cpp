#include "entity_inspector.h"

#include <imgui.h>
#include <awesome/scene/component.h>
#include <awesome/scene/entity.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/sprite_renderer.h>

EntityInspector::EntityInspector()
{
}


void EntityInspector::render(Entity* const entity)
{
	ImGui::Begin("Entity Inspector");
	if (entity)
	{
		ImGui::InputText("name", const_cast<char*>(entity->name.c_str()), 100);
		ImGui::InputText("tag", const_cast<char*>(entity->tag.c_str()), 100);
		ImGui::InputFloat3("position", entity->transform.position.data);
		ImGui::InputFloat3("rotation", entity->transform.rotation.data);
		ImGui::InputFloat3("scale", entity->transform.scale.data);
		ImGui::Checkbox("isStatic", &entity->transform.isStatic);

		const auto& components = entity->getComponents();
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			Component* const component = *it;
			if (SpriteRenderer* const renderer = dynamic_cast<SpriteRenderer*>(component))
			{
				ImGui::Separator();
				ImGui::Text("SpriteRenderer");
				ImGui::InputFloat4("rect", renderer->rect.data);
			}
			if (GizmosRenderer* const renderer = dynamic_cast<GizmosRenderer*>(component))
			{
				ImGui::Separator();
				ImGui::Text("GizmosRenderer");
				ImGui::ColorEdit4("background", renderer->color.data);
			}
		}
	}
	ImGui::End();
}