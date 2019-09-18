#pragma once 

#include <vector>
#include <unordered_map>
#include "entity.h"

namespace ECS
{
	template <class T>
	class System
	{
	public:

		System()
			: m_components()
			, m_entityComponents()
		{
		}

		~System()
		{
			clear();
		}

		inline const std::vector<T> getComponents() const { return m_components; }

		template <typename... P>
		inline T* addComponent(const Entity::id_t t_entityId, P... t_args)
		{
			m_components.push_back(new T(std::forward<P>(t_args)...));
			T* const component_ptr = m_components.back();
			m_entityComponents.insert({ t_entityId, component_ptr });
			return component_ptr;
		}

		inline T* getComponent(const Entity::id_t t_entityId) const
		{
			auto it = m_entityComponents.find(t_entityId);
			if (it != m_entityComponents.end())
			{
				return it->second;
			}
			return nullptr;
		}

		inline void removeComponent(const Entity::id_t t_entityId)
		{
			auto it = m_entityComponents.find(t_entityId);
			if (it != m_entityComponents.end())
			{
				auto c_it = std::find(m_components.begin(), m_components.end(), it->second);
				m_components.erase(c_it);
				delete it->second;
				m_entityComponents.erase(it);
			}
		}

		inline void clear()
		{
			m_entityComponents.clear();
			for (auto component : m_components)
				delete component;
			m_components.clear();
		}

	private:

		std::vector<T*> m_components;
		std::unordered_map<Entity::id_t, T*> m_entityComponents;
	};
}