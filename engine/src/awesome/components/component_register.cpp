#include "component_register.h"

#include "component_library.h"

// components
#include "sprite_renderer_component.h"

void ComponentRegister::execute()
{
	ComponentLibrary& library = ComponentLibrary::instance();
	{
		library.push_back({ "SpriteRenderer", "Graphics", []() -> Component* { return new SpriteRendererComponent(); } });
	}
}