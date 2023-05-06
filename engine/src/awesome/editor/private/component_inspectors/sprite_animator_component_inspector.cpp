#include "sprite_animator_component_inspector.h"

#include <awesome/components/sprite_animator_component.h>
#include <awesome/editor/editor_ui.h>

bool SpriteAnimatorComponentInspector::canInspect(Component& component) const
{
	return component.type_name() == reflect::Type<SpriteAnimatorComponent>::name();
}

void SpriteAnimatorComponentInspector::inspect(Component& component)
{
	ComponentInspector::inspect(component);
	SpriteAnimatorComponent& animator = dynamic_cast<SpriteAnimatorComponent&>(component);
	EditorUI::input("Animations", animator.animations);
}