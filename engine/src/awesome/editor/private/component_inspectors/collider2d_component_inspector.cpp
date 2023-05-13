#include "collider2d_component_inspector.h"

#include <awesome/components/collider2d_component.h>
#include <awesome/editor/editor_ui.h>

bool Collider2DComponentInspector::canInspect(Component& component) const
{
	return component.type_name() == reflect::Type<Collider2DComponent>::name();
}

void Collider2DComponentInspector::inspect(Component& component)
{
	Collider2DComponent& collider = dynamic_cast<Collider2DComponent&>(component);
	EditorUI::input("enabled", collider.enabled);
	const ColliderType2D last_type = collider.m_type;
	EditorUI::input("Type", collider.m_type);
	if (last_type != collider.m_type)
	{
		collider.update_aabb();
	}

	if (collider.m_type == ColliderType2D::Circle)
	{
		EditorUI::input("Radius", collider.bounds.x);
	}
	else
	{
		EditorUI::input("Bounds", collider.bounds);
	}
	EditorUI::input("Is Trigger", collider.isTrigger);
}