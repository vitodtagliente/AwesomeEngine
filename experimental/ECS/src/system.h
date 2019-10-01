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

		inline entity_t getEntity(const size_t t_index) const
		{
			return m_entities[t_index];
		}

		void removeComponent(const size_t t_entityId)
		{
			auto it = std::find(m_components.begin(), m_components.end(), [t_entityId](const DataComponent<T>& t_component) {
				return t_component.entityId = t_entityId;
			});
		}

		inline void clear()
		{
			m_components.clear();
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