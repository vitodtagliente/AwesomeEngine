#pragma once 

#include <cassert>
#include <vector>
#include "data_component.h"
#include "type_id.h"

namespace ECS
{
	class BaseSystem
	{
	public:

		virtual void update(const float t_deltaTime) = 0;
	};

	template <class T>
	class System : public BaseSystem
	{
	public:

		using component_t = DataComponent<T>;

		System()
			: m_components()
		{
		}

		~System() = default;

		inline const std::vector<T>& getComponents() const { return m_components; }

		template <typename... P>
		inline void addComponent(const id_t t_entityId, P... t_args)
		{
			m_components.push_back(DataComponent<T>(
				++id_counter,
				t_entityId,
				T{ std::forward<P>(t_args)... })
			);
		}

		void removeComponent(const id_t t_entityId)
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

		static id_t id_counter;
	};

	template <typename T>
	id_t System<T>::id_counter = 0;
}