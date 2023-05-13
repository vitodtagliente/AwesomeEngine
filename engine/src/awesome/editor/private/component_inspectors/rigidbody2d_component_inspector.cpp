#include "rigidbody2d_component_inspector.h"

#include <awesome/components/rigidbody2d_component.h>
#include <awesome/editor/editor_ui.h>

bool Rigidbody2DComponentInspector::canInspect(Component& component) const
{
	return component.type_name() == reflect::Type<Rigidbody2DComponent>::name();
}

void Rigidbody2DComponentInspector::inspect(Component& component)
{
	Rigidbody2DComponent& body = dynamic_cast<Rigidbody2DComponent&>(component);
	EditorUI::input("enabled", body.enabled);
	EditorUI::input("Type", body.m_type);
	EditorUI::input("Freeze Rotation", body.freezeRotation);
	EditorUI::input("Gravity Scale", body.gravityScale);
	EditorUI::input("Mass", body.mass);
}