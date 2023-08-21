#include "component_array.h"

IComponentArray* const ComponentRegistry::find(const std::size_t id)
{
	const auto& it = s_lookup.find(id);
	if (it != s_lookup.end())
	{
		return it->second;
	}
	return nullptr;
}

IComponentArray& ComponentRegistry::get(const std::size_t id)
{
	return *s_lookup[id];
}

void ComponentRegistry::clear()
{
	for (auto& component_array : s_components)
	{
		component_array->clear();
	}
}

void ComponentRegistry::flush()
{
	for (auto& component_array : s_components)
	{
		component_array->flush();
	}
}

void ComponentRegistry::erase(const uuid& entity)
{
	for (auto& component_array : s_components)
	{
		component_array->erase(entity);
	}
}

void ComponentRegistry::queue_free(const uuid& entity)
{
	for (auto& component_array : s_components)
	{
		component_array->queue_free(entity);
	}
}

void ComponentRegistry::register_component(IComponentArray* const instance)
{
	static std::size_t s_counter{ 0 };
	instance->m_id = static_cast<std::size_t>(std::pow(2, s_counter++));

	s_components.push_back(instance);
	s_lookup.insert(std::make_pair(instance->id(), instance));
}
