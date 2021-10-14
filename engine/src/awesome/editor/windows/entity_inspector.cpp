#include "entity_inspector.h"

#include <imgui.h>
#include <typeinfo>

#include <awesome/entity/entity.h>

#include "../context.h"
#include "scene_inspector.h"

namespace editor
{
	EntityInspector::EntityInspector()
		: Window()
	{
	}

	std::string EntityInspector::getTitle() const
	{
		return "Entity";
	}

	void EntityInspector::render(Context& context)
	{
		if (SceneInspector* const inspector = SceneInspector::instance())
		{
			Entity* const entity = inspector->getSelectedEntity();
			if (entity != nullptr)
			{
				context.input("name", &entity->name, 100);
				context.input("tag", &entity->tag, 100);
				context.input("position", &entity->transform.position);
				context.input("rotation", &entity->transform.rotation);
				context.input("scale", &entity->transform.scale);
				context.input("static", &entity->transform.isStatic);

				const auto& components = entity->getComponents();
				for (auto it = components.begin(); it != components.end(); ++it)
				{
					Component* const component = *it;
					if (context.collapsingHeader(typeid(*component).name()))
					{
						context.input("enabled", &component->enabled);
					}
				}
			}
		}
	}
}