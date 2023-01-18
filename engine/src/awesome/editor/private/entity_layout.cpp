#include "entity_layout.h"

#include <awesome/component/sprite_renderer_component.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/graphics/color.h>

void EntityLayout::input(Entity* const entity)
{
	if (entity == nullptr) return;

	Layout::beginContext("entity");
	Layout::button(entity->getTypeName(), graphics::Color(1.f, .6f, .6f));
	Layout::sameLine();
	Layout::button(static_cast<std::string>(entity->getId()), graphics::Color(0.f, .6f, .6f));
	Layout::input("Name", entity->name);
	Layout::input("Tag", entity->tag);
	Layout::separator();
	Layout::input("Position", entity->transform.position);
	Layout::input("Rotation", entity->transform.rotation);
	Layout::input("Scale", entity->transform.scale);
	Layout::input("Persistent", entity->persistent);
	Layout::hint("If true, the entity is not destroyed during the loading of a new scene");
	Layout::sameLine();
	Layout::input("Transient", entity->transient);
	Layout::hint("If true, the entity cannot be saved as part of the scene serialization");
	Layout::input("Replicate", entity->replicate);
	Layout::hint("If true, the entity can be replicated in multiplayer games");
	Layout::input("Static", entity->transform.isStatic);
	Layout::hint("If true, the entity cannot move. It helps optimizing the transform's computation");
	Layout::endContext();

	Layout::separator();

	if (Layout::beginCombo(TextIcon::plus(" Add Component"), ""))
	{
		const std::vector<TypeDefinition>& types = TypeFactory::list("Type", "Component");
		for (const TypeDefinition& type : types)
		{
			const auto& it = std::find_if(entity->getComponents().begin(), entity->getComponents().end(), [&type](const std::unique_ptr<Component>& component) -> bool
				{
					return component->getTypeName() == type.name;
				}
			);

			// add one component only per type
			if (it != entity->getComponents().end())
			{
				continue;
			}

			if (Layout::selectable(type.name.c_str(), false))
			{
				Component* const component = TypeFactory::instantiate<Component>(type);
				if (component)
				{
					entity->addComponent(component);
					Layout::endCombo();
					return; // force the refresh of the inspector
				}
			}
		}
		Layout::endCombo();
	}

	for (const auto& component : entity->getComponents())
	{
		const std::string& componentName = component->getTypeName();
		Layout::beginContext(componentName);
		if (Layout::collapsingHeader(componentName))
		{
			component->inspect();
			Layout::separator();
			if (Layout::button(TextIcon::minus(" Remove Component")))
			{
				entity->removeComponent(component->getId());
				Layout::endContext();
				return; // force the refresh of the inspector
			}
		}
		Layout::endContext();
	}

	// preview the sprite
	{
		SpriteRendererComponent* const component = entity->findComponent<SpriteRendererComponent>();
		if (component && component->image && component->image->state == Asset::State::Ready)
		{
			Layout::separator();
			Layout::image(component->image, component->rect);
		}
	}
}