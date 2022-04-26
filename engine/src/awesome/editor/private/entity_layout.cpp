#include "entity_layout.h"

#include <awesome/components/sprite_renderer.h>
#include <awesome/core/reflection.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/text_icon.h>

namespace editor
{
	void EntityLayout::input(Entity& entity)
	{
		Layout::beginContext("entity");
		Layout::input("Name", entity.name);
		Layout::input("Tag", entity.tag);
		Layout::separator();
		Layout::input("Position", entity.transform.position);
		Layout::input("Rotation", entity.transform.rotation);
		Layout::input("Scale", entity.transform.scale);
		Layout::input("Static", entity.transform.isStatic);
		Layout::endContext();

		Layout::separator();

		if (Layout::beginCombo(TextIcon::plus(" Add Component"), ""))
		{
			static std::set<std::string> types = TypeFactory::list("Component");
			for (const std::string& type : types)
			{
				if (Layout::selectable(type.c_str(), false))
				{
					Component* const component = TypeFactory::instantiate<Component>(type);
					if (component)
					{
						entity.addComponent(component);
						Layout::endCombo();
						return; // force the refresh of the inspector
					}
				}
			}
			Layout::endCombo();
		}

		for (const auto& component : entity.getComponents())
		{
			const std::string& componentName = component->getTypeDescriptor().name;
			Layout::beginContext(componentName);
			if (Layout::collapsingHeader(componentName))
			{
				component->inspect();
				Layout::separator();
				if (Layout::button(TextIcon::minus(" Remove Component")))
				{
					entity.removeComponent(component->getId());
					return; // force the refresh of the inspector
				}
			}
			Layout::endContext();
		}

		// preview the sprite
		{
			SpriteRenderer* const component = entity.findComponent<SpriteRenderer>();
			if (component && component->sprite && component->sprite->data.has_value())
			{
				Layout::separator();
				Layout::image(component->sprite->data.value().image, component->sprite->data.value().rect);
			}
		}
	}
}