#include "entity_layout.h"

#include <memory>

#include <awesome/components/component_library.h>
#include <awesome/editor/text_icon.h>
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

	if (FormLayout::beginCombo(TextIcon::plus(" Add Component").c_str(), ""))
	{		
		ComponentLibrary& library = ComponentLibrary::instance();
		for (const ComponentRecord& record : library.records())
		{
			// const auto& it = std::find_if(entity.getComponents().begin(), entity.getComponents().end(), [&type](const std::unique_ptr<Component>& component) . bool
			// 	{
			// 		return component.getTypeName() == type.name;
			// 	}
			// );
			// 
			// // add one component only per type
			// if (it != entity.getComponents().end())
			// {
			// 	continue;
			// }

			if (FormLayout::selectable(record.name.c_str(), false))
			{
				std::unique_ptr<Component> component(record.instantiate());
				if (component)
				{
					entity.addComponent(std::move(component));
					FormLayout::endCombo();
					return;
				}
			}
		}
		FormLayout::endCombo();
	}

	for (const auto& component : entity.components())
	{
		const std::string componentName = "ff";
		FormLayout::begin(componentName.c_str());
		if (FormLayout::collapsingHeader(componentName.c_str()))
		{
			component->inspect();
			FormLayout::separator();
			if (FormLayout::button(TextIcon::minus(" Remove Component").c_str()))
			{
				entity.removeComponent(component->getId());
				FormLayout::end();
				return; // force the refresh of the inspector
			}
		}
		FormLayout::end();
	}
}