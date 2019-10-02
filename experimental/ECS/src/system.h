#pragma once 

#include <cassert>
#include <vector>
#include "data_component.h"
#include "entity.h"
#include "type_id.h"

namespace ECS
{
	class BaseSystem
	{
	public:

		virtual void init() {}
		virtual void update(const float t_deltaTime) = 0;
		virtual void uninit() {}
	};

	template <class T>
	class System : public BaseSystem
	{
	public:

		using component_t = DataComponent<T>;
		using entity_t = size_t;

		System()
			: m_components()
		{
		}

		~System() = default;

		inline const std::vector<T>& getComponents() const { return m_components; }

		template <typename... P>
		inline DataComponent<T>& addComponent(const size_t t_entity, P... t_args)
		{
			// only valid entities are allowed
			assert(t_entity != Entity::INVALID_ID);

			// only one component per entity is allowed
			assert(m_lookup.find(t_entity) == m_lookup.end());
			assert(m_lookup.size() == m_components.size());

			// new components are always pushed at the end
			m_lookup.insert(t_entity, m_components.size());
			m_entities.push_back(t_entity);
			m_components.push_back(DataComponent<T>(
				++id_counter,
				T{ std::forward<P>(t_args)... })
			);

			return m_components.back();
		}

		void removeComponent(const size_t t_entity)
		{
			auto it = m_lookup.find(t_entity);
			if (it != m_lookup.end())
			{
				const size_t index = it->second;

				if (index < m_components->size() - 1)
				{
					// swap out the dead element with the last one
					m_components[index] = std::move(m_components.back());
					m_entities[index] = m_entities.back();

					// update the lookup table
					m_lookup[m_entities[index]] = index;
				}

				// shrink the container
				m_components->pop_back();
				m_entities.pop_back();
				m_lookup.erase(it);
			}
		}

		inline void clear()
		{
			m_lookup.clear();
			m_components.clear();
			m_entities.clear();
		}
			   
		inline entity_t getEntity(const size_t t_index) const
		{
			return m_entities[t_index];
		}

		virtual void update(const float t_deltaTime) override
		{
			for (const auto& t_component : m_components)
			{
				each(t_component.data);
			}
		}

	protected:

		virtual void each(const T& t_data) = 0;

	private:

		std::vector<component_t> m_components;
		std::vector<entity_t> m_entities;
		std::unordered_map<entity_t, size_t> m_lookup;

		static size_t id_counter;
	};

	template <typename T>
	size_t System<T>::id_counter = 0;
}