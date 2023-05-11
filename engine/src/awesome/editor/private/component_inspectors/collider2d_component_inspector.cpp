#include "collider2d_component_inspector.h"

#include <awesome/components/collider2d_component.h>
#include <awesome/editor/editor_ui.h>

bool Collider2dComponentInspector::canInspect(Component& component) const
{
	return component.type_name() == reflect::Type<Collider2dComponent>::name();
}

void Collider2dComponentInspector::inspect(Component& component)
{
	Collider2dComponent& collider = dynamic_cast<Collider2dComponent&>(component);
	EditorUI::input("enabled", collider.enabled);
	EditorUI::input("Type", collider.m_type);
	if (collider.m_type == Collision2DShapeType::Circle)
	{
		EditorUI::input("Radius", collider.bounds.x);
	}
	else
	{
		EditorUI::input("Bounds", collider.bounds);
	}
	EditorUI::input("Is Trigger", collider.isTrigger);
}