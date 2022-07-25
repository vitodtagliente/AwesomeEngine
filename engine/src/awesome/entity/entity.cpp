#include "entity.h"

#include <awesome/graphics/graphics_component.h>
#include <awesome/graphics/renderer.h>
#include <awesome/net/network_manager.h>

void Entity::prepareToSpawn()
{
	for (const auto& component : m_components)
	{
		if (component->enabled)
		{
			component->init();
		}
	}

	m_state = State::Alive;
}

void Entity::prepareToDestroy()
{
	for (const auto& component : m_components)
	{
		component->uninit();
	}
	m_components.clear();

	for (const auto& child : m_children)
	{
		child->prepareToDestroy();
	}
	m_children.clear();

	m_state = State::PendingDestroy;
}

void Entity::setParent(Entity* const entity)
{
	m_parent = entity;
}

void Entity::update(const double deltaTime)
{
	for (const auto& component : m_components)
	{
		if (component->enabled
			&& (!replicate || net::NetworkManager::instance().hasNetworkAuthority(component->getNetMode())))
		{
			component->update(deltaTime);
		}
	}
	transform.update();
}

void Entity::duplicate(const Entity& from, Entity& duplicate)
{
	const uuid id = duplicate.m_id;
	duplicate.deserialize(from.serialize());
	duplicate.m_id = id;
}

void Entity::duplicate(const PrefabAssetPtr& prefab, Entity& duplicate)
{
	if (prefab->data.has_value())
	{
		const uuid id = duplicate.m_id;
		duplicate.deserialize(prefab->data.value());
		duplicate.m_id = id;
		duplicate.m_prefab = prefab->descriptor.id;
	}
}

void Entity::render(graphics::Renderer2D* const renderer)
{
	for (const auto& component : m_components)
	{
		if (!component->enabled) continue;


		if (graphics::IGraphicsComponent* const graphicsComponent = dynamic_cast<graphics::IGraphicsComponent*>(component.get()))
		{
			graphicsComponent->render(renderer);
		}
	}
}

bool Entity::operator==(const Entity& other) const
{
	return m_id == other.m_id;
}

bool Entity::operator!=(const Entity& other) const
{
	return m_id != other.m_id;
}

void Entity::removeComponent(Component* const component)
{
	removeComponent(component->getId());
}

void Entity::removeComponent(const uuid& id)
{
	const auto& it = std::find_if(m_components.begin(), m_components.end(), [&id](const std::unique_ptr<Component>& component) -> bool
		{
			return component->getId() == id;
		}
	);

	if (it != m_components.end())
	{
		(*it)->detach();
		m_components.erase(it);
	}
}

json::value Entity::serialize() const
{
	static const auto& entitiesToJson = [](const std::vector<std::unique_ptr<Entity>>& entities) -> json::value
	{
		json::value data = json::array();
		for (const auto& entity : entities)
		{
			data.push_back(entity->serialize());
		}
		return data;
	};

	static const auto& componentsToJson = [](const std::vector<std::unique_ptr<Component>>& components) -> json::value
	{
		json::value data = json::array();
		for (const auto& component : components)
		{
			data.push_back(component->serialize());
		}
		return data;
	};

	return json::object({
		{"id", ::serialize(m_id)},
		{"name", name},
		{"replicate", replicate},
		{"tag", tag},
		{"transform", ::serialize(transform)},
		{"children", entitiesToJson(m_children)},
		{"components", componentsToJson(m_components)}
		});
}

void Entity::deserialize(const json::value& value)
{
	if (!value.is_object())
		return;

	m_children.clear();
	m_components.clear();

	::deserialize(value["id"], m_id);
	replicate = value.safeAt("replicate").as_bool(false);
	name = value.safeAt("name").as_string("");
	tag = value.safeAt("tag").as_string("");
	::deserialize(value["transform"], transform);

	const json::value::array_t& components = value["components"].as_array();
	for (const json::value& data : components)
	{
		const std::string& type = data["componentclass"].as_string();
		Component* const component = TypeFactory::instantiate<Component>(type);
		if (component != nullptr)
		{
			addComponent(component)->deserialize(data);
		}
	}
}
