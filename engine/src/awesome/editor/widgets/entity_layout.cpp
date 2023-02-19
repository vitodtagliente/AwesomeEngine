#include "entity_layout.h"

#include <awesome/graphics/color.h>
#include <awesome/scene/entity.h>

#include "form_layout.h"

void EntityLayout::input(Entity& entity)
{
	FormLayout::begin("entity");
	FormLayout::button(entity.tag.c_str(), graphics::Color(1.f, .6f, .6f));
	FormLayout::sameLine();
	FormLayout::button(static_cast<std::string>(entity.id()).c_str(), graphics::Color(0.f, .6f, .6f));
	FormLayout::input("Name", entity.name);
	FormLayout::input("Tag", entity.tag);
	FormLayout::separator();
	FormLayout::input("Position", entity.transform.position);
	FormLayout::input("Rotation", entity.transform.rotation);
	FormLayout::input("Scale", entity.transform.scale);
	FormLayout::input("Persistent", entity.persistent);
	FormLayout::hint("If true, the entity is not destroyed during the loading of a new scene");
	FormLayout::sameLine();
	FormLayout::input("Transient", entity.transient);
	FormLayout::hint("If true, the entity cannot be saved as part of the scene serialization");
	FormLayout::input("Replicate", entity.replicate);
	FormLayout::hint("If true, the entity can be replicated in multiplayer games");
	FormLayout::input("Static", entity.transform.isStatic);
	FormLayout::hint("If true, the entity cannot move. It helps optimizing the transform's computation");
	FormLayout::end();

	FormLayout::separator();

	/*
	if (Layout::beginCombo(TextIcon::plus(" Add Component"), ""))
	{
		const std::vector<TypeDefinition>& types = TypeFactory::list("Type", "Component");
		for (const TypeDefinition& type : types)
		{
			const auto& it = std::find_if(entity.getComponents().begin(), entity.getComponents().end(), [&type](const std::unique_ptr<Component>& component) . bool
				{
					return component.getTypeName() == type.name;
				}
			);

			// add one component only per type
			if (it != entity.getComponents().end())
			{
				continue;
			}

			if (Layout::selectable(type.name.c_str(), false))
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
	*/

	for (const auto& component : entity.components())
	{
		// const std::string& componentName = component.getTypeName();
		// Layout::beginContext(componentName);
		// if (Layout::collapsingHeader(componentName))
		// {
		// 	component.inspect();
		// 	Layout::separator();
		// 	if (Layout::button(TextIcon::minus(" Remove Component")))
		// 	{
		// 		entity.removeComponent(component.getId());
		// 		Layout::endContext();
		// 		return; // force the refresh of the inspector
		// 	}
		// }
		// Layout::endContext();
	}
}