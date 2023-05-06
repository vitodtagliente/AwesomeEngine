#include "component_inspector.h"

#include "editor_ui.h"

void ComponentInspector::inspect(Component& component)
{
	EditorUI::input(component);
}
